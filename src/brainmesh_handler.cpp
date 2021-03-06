#include "brainmesh_handler.h"
#include "rttvis_gui.h"

#ifdef HAVE_VTK7
#include "ui_rttvis_gui_VTK7.h"
#endif

#ifdef HAVE_VTK8
#include "ui_rttvis_gui_VTK8.h"
#endif

#ifdef HAVE_VTK9
#include "ui_rttvis_gui_VTK9.h"
#endif



vtkSmartPointer<vtkPolyData> cleanMesh(vtkSmartPointer<vtkPolyData> inp) {
	auto cleaned = vtkSmartPointer<vtkCleanPolyData>::New();
	cleaned->SetInputData(inp);
	cleaned->Update();

	return cleaned->GetOutput();
}

vtkSmartPointer<vtkPolyData> fixMesh(vtkSmartPointer<vtkPolyData> inp) {

	auto normals = vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputData(inp);
	normals->SetFeatureAngle(160);
	normals->SplittingOn();
	normals->ConsistencyOn();
	normals->AutoOrientNormalsOn();
	normals->Update();

	return normals->GetOutput();

}

vtkSmartPointer<vtkPolyData> upsample(vtkSmartPointer<vtkPolyData> inp) {

	auto triangles = vtkSmartPointer<vtkTriangleFilter>::New();
	triangles->SetInputData(inp);
	triangles->Update();

	auto subdivisionFilter =  vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
	subdivisionFilter->SetInputData(triangles->GetOutput());
	subdivisionFilter->SetNumberOfSubdivisions(2);
	subdivisionFilter->Update();

	return subdivisionFilter->GetOutput();
}


vtkSmartPointer<vtkPolyData> smooth(vtkSmartPointer<vtkPolyData> inp) {

	auto smoother = vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New();
	smoother->SetInputData(inp);
	smoother->SetNumberOfIterations(20);
	smoother->BoundarySmoothingOn();
	smoother->FeatureEdgeSmoothingOn();
	smoother->SetFeatureAngle(175);
	smoother->SetPassBand(0.1);
	smoother->NonManifoldSmoothingOn();
	smoother->NormalizeCoordinatesOn();
	smoother->Update();

	return smoother->GetOutput();
}



vtkSmartPointer<vtkPolyData> downsample(vtkSmartPointer<vtkPolyData> inp) {

	vtkSmartPointer<vtkSurface> surface = vtkSurface::New();
	surface->CreateFromPolyData(inp);

	auto areas = vtkSmartPointer<vtkDoubleArray>::New();
	areas = surface->GetTrianglesAreas();
	double surfaceArea=0;

	for (int i=0; i<areas->GetSize(); i++)
		surfaceArea += areas->GetValue(i);

    // Sets the resolution of the peel mesh
	int clusterNumber = surfaceArea/30;
    // int clusterNumber = surfaceArea/20;

	vtkSmartPointer<vtkIsotropicDiscreteRemeshing> Remesh = vtkIsotropicDiscreteRemeshing::New();
	Remesh->SetInput(surface);
	Remesh->SetFileLoadSaveOption(0);
	Remesh->SetNumberOfClusters(clusterNumber);
	Remesh->SetConsoleOutput(0);
	Remesh->GetMetric()->SetGradation(0);
	Remesh->SetDisplay(0);
	Remesh->Remesh();

	auto out = vtkSmartPointer<vtkPolyData>::New();
	out->SetPoints(Remesh->GetOutput()->GetPoints());
	out->SetPolys(Remesh->GetOutput()->GetPolys());

	return out;

}

void Brain::sliceDown() {

	// Warp using the normals
	auto warp = vtkSmartPointer<vtkWarpVector>::New();
	warp->SetInputData(fixMesh(downsample(currentPeel))); // fixMesh here updates normals needed for warping
	warp->SetInputArrayToProcess(0, 0, 0,
			vtkDataObject::FIELD_ASSOCIATION_POINTS,
			vtkDataSetAttributes::NORMALS);
	warp->SetScaleFactor(-1);
	warp->Update();

	auto out = vtkSmartPointer<vtkPolyData>::New();
	out = upsample(warp->GetPolyDataOutput());
	out = smooth(out);
	out = fixMesh(out);
	out = cleanMesh(out);

	currentPeel = out;
}

void Brain::mapImageOnCurrentPeel() {

	xyz2_refImageSpace->SetInputData(currentPeel);
	xyz2_refImageSpace->Update();

	auto probe = vtkSmartPointer<vtkProbeFilter>::New();
	probe->SetInputData(xyz2_refImageSpace->GetOutput());
	probe->SetSourceData(refImage);
	probe->Update();

	refImageSpace2_xyz->SetInputData(probe->GetOutput());
	refImageSpace2_xyz->Update();

	currentPeel = refImageSpace2_xyz->GetOutput();

}

void Brain::peelDown() {

	RTTVIS* rtt	= static_cast<RTTVIS*>(rttvis);

	rtt->ui.progressText->setText("Peeling");

	for (int i=0; i<numberOfPeels; i++) {
		sliceDown();
		mapImageOnCurrentPeel();

		auto newPeel = vtkSmartPointer<vtkPolyData>::New();
		newPeel->DeepCopy(currentPeel);
		peel.push_back(newPeel);

		currentPeelNo++;
		rtt->ui.progressBar->setValue(currentPeelNo+5);
	}

}


vtkSmartPointer<vtkActor> Brain::getPeelActor(int p) {
	vtkNew<vtkNamedColors> colors;

	// Create the color map
	vtkSmartPointer<vtkLookupTable> colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	colorLookupTable->SetNumberOfColors(512);
	colorLookupTable->SetSaturationRange(0,0);
	colorLookupTable->SetHueRange(0,0);
	colorLookupTable->SetValueRange(0,2.5);
	colorLookupTable->SetTableRange(refImage->GetScalarRange());
	colorLookupTable->Build();

	// Set mapper
	auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
	mapper->SetInputData(peel[p]);
	mapper->SetScalarRange(refImage->GetScalarRange());
	mapper->SetLookupTable(colorLookupTable);
	mapper->InterpolateScalarsBeforeMappingOn();

	// Set actor
	currentPeelActor->SetMapper(mapper);

	return currentPeelActor;
}


vtkSmartPointer<vtkActor> Brain::getCurrentPeelActor() {

	vtkNew<vtkNamedColors> colors;


	// Create the color map
	vtkSmartPointer<vtkLookupTable> colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	colorLookupTable->SetNumberOfColors(512);
	colorLookupTable->SetSaturationRange(0,0);
	colorLookupTable->SetHueRange(0,0);
	colorLookupTable->SetValueRange(0,2.5);
	colorLookupTable->SetTableRange(refImage->GetScalarRange());
	colorLookupTable->Build();

	// Set mapper
	auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
	mapper->SetInputData(currentPeel);
	mapper->SetScalarRange(refImage->GetScalarRange());
	mapper->SetLookupTable(colorLookupTable);
	mapper->InterpolateScalarsBeforeMappingOn();

	// Set actor
	currentPeelActor->SetMapper(mapper);
	currentPeelActor->GetProperty()->SetBackfaceCulling(1);
	currentPeelActor->GetProperty()->SetOpacity(0.5);
    // currentPeelActor->GetProperty()->SetOpacity(0.25);

	return currentPeelActor;

}

Brain::Brain(std::string T1_fname, std::string mask_fname, void* _rttvis) {

	rttvis 		= _rttvis;

	RTTVIS* rtt	= static_cast<RTTVIS*>(_rttvis);

	// Read reference image
	rtt->ui.progressText->setText("Reading T1");
	auto T1_reader = vtkSmartPointer<vtkNIFTIImageReader>::New();
	T1_reader->SetFileName(T1_fname.c_str());
	T1_reader->Update();
	rtt->ui.progressBar->setValue(1);

	refImage = vtkSmartPointer<vtkImageData>::New();
	refImage = T1_reader->GetOutput();

	// Read for reference surface
	rtt->ui.progressText->setText("Reading Mask");
	auto mask_reader = vtkSmartPointer<vtkNIFTIImageReader>::New();
	mask_reader->SetFileName(mask_fname.c_str());
	mask_reader->Update();
	rtt->ui.progressBar->setValue(2);

	// Zero-padding
	rtt->ui.progressText->setText("Zero padding");
	auto padFilter = vtkSmartPointer<vtkImageConstantPad>::New();
	padFilter->SetInputConnection(mask_reader->GetOutputPort());
	padFilter->SetConstant(0);
	int extent[6];
	refImage->GetExtent(extent);
	padFilter->SetOutputWholeExtent(extent[0]-1,extent[1]+1,extent[2]-1,extent[3]+1,extent[4]-1,extent[5]+1);
	padFilter->GetOutput();
	rtt->ui.progressBar->setValue(3);

	// Apply morphological closing
	rtt->ui.progressText->setText("Filling holes");
	auto openClose = vtkSmartPointer<vtkImageOpenClose3D>::New();
	openClose->SetInputConnection(padFilter->GetOutputPort());
	openClose->SetOpenValue(0);
	openClose->SetCloseValue(1);
	openClose->SetKernelSize(11, 11, 11);
	openClose->ReleaseDataFlagOff();
	openClose->GetOutput();
	openClose->GetCloseValue();
	rtt->ui.progressBar->setValue(4);	

	// Prep mesh
	rtt->ui.progressText->setText("Preparing surface mesh");
	auto mc = vtkSmartPointer<vtkContourFilter>::New();
	mc->SetInputConnection(openClose->GetOutputPort());
	mc->SetValue(0, 1);
	mc->Update();


	refSurface = vtkSmartPointer<vtkPolyData>::New();
	refSurface = mc->GetOutput();

	auto tmpPeel = vtkSmartPointer<vtkPolyData>::New();
	tmpPeel    	 = downsample(refSurface);


	auto mask_sFormMatrix 		= vtkSmartPointer<vtkMatrix4x4>::New();
	mask_sFormMatrix 			= mask_reader->GetSFormMatrix();

	auto mask_ijk2xyz			= vtkSmartPointer<vtkTransform>::New();
	mask_ijk2xyz->SetMatrix(mask_sFormMatrix);

	auto mask_ijk2xyz_filter 	= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	mask_ijk2xyz_filter->SetInputData(tmpPeel);
	mask_ijk2xyz_filter->SetTransform(mask_ijk2xyz);
	mask_ijk2xyz_filter->Update();

	tmpPeel = smooth(mask_ijk2xyz_filter->GetOutput());
	tmpPeel = fixMesh(tmpPeel);
	tmpPeel = cleanMesh(tmpPeel);
	tmpPeel = upsample(tmpPeel);
	tmpPeel = smooth(tmpPeel);
	tmpPeel = fixMesh(tmpPeel);
	tmpPeel = cleanMesh(tmpPeel);


	auto sFormMatrix 					= vtkSmartPointer<vtkMatrix4x4>::New();
	// sFormMatrix 						= T1_reader->GetQFormMatrix();
	sFormMatrix 						= T1_reader->GetSFormMatrix();

	auto refImageSpace2_xyz_transform 	= vtkSmartPointer<vtkTransform>::New();
	refImageSpace2_xyz_transform->SetMatrix(sFormMatrix);

	refImageSpace2_xyz 	= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	refImageSpace2_xyz->SetTransform(refImageSpace2_xyz_transform);

	auto xyz2_refImageSpace_transform 	= vtkSmartPointer<vtkTransform>::New();
	sFormMatrix->Invert();
	xyz2_refImageSpace_transform->SetMatrix(sFormMatrix);

	xyz2_refImageSpace 					= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	xyz2_refImageSpace->SetTransform(xyz2_refImageSpace_transform);

	// Prepare current peel
	currentPeel	 	= vtkSmartPointer<vtkPolyData>::New();
	currentPeel 	= tmpPeel;
	currentPeelNo 	= 0;
	mapImageOnCurrentPeel();
	auto newPeel = vtkSmartPointer<vtkPolyData>::New();
	newPeel->DeepCopy(currentPeel);
	peel.push_back(newPeel);
	currentPeelActor = vtkSmartPointer<vtkActor>::New();
	getCurrentPeelActor();
	peelActors.push_back(currentPeelActor);

	numberOfPeels = 30;
	rtt->ui.progressBar->setValue(5);

	// Start peeling
	peelDown();

}



vtkSmartPointer<vtkPolyData> brain_downsample(vtkSmartPointer<vtkPolyData> inp) {

	vtkSmartPointer<vtkSurface> surface = vtkSurface::New();
	surface->CreateFromPolyData(inp);

	auto areas = vtkSmartPointer<vtkDoubleArray>::New();
	areas = surface->GetTrianglesAreas();
	double surfaceArea=0;

	for (int i=0; i<areas->GetSize(); i++)
		surfaceArea += areas->GetValue(i);

	int clusterNumber = surfaceArea/2;

	vtkSmartPointer<vtkIsotropicDiscreteRemeshing> Remesh = vtkIsotropicDiscreteRemeshing::New();
	Remesh->SetInput(surface);
	Remesh->SetFileLoadSaveOption(0);
	Remesh->SetNumberOfClusters(clusterNumber);
	Remesh->SetConsoleOutput(0);
	Remesh->GetMetric()->SetGradation(0);
	Remesh->SetDisplay(0);
	Remesh->Remesh();

	auto out = vtkSmartPointer<vtkPolyData>::New();
	out->SetPoints(Remesh->GetOutput()->GetPoints());
	out->SetPolys(Remesh->GetOutput()->GetPolys());

	return out;

}

