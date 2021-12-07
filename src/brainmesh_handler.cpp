#include "brainmesh_handler.h"

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

	std::cout << "Peeling down: " << std::flush;
	for (int i=0; i<numberOfPeels; i++) {
		sliceDown();
		mapImageOnCurrentPeel();

		auto newPeel = vtkSmartPointer<vtkPolyData>::New();
		newPeel->DeepCopy(currentPeel);
		peel.push_back(newPeel);

		//		getCurrentPeelActor();
		//		auto newPeelActor = vtkSmartPointer<vtkActor>::New();
		//		newPeelActor = currentPeelActor;
		//		peelActors.push_back(newPeelActor);

		currentPeelNo++;
		std::cout << currentPeelNo << " " << std::flush;
	}

	std::cout << std::endl;
}

vtkSmartPointer<vtkActor> Brain::getPeelActor(int p) {
	vtkNew<vtkNamedColors> colors;


	// Create the color map
	vtkSmartPointer<vtkLookupTable> colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
	colorLookupTable->SetNumberOfColors(512);
	colorLookupTable->SetSaturationRange(0,0);
	colorLookupTable->SetHueRange(0,0);
	colorLookupTable->SetValueRange(0,1);
	// colorLookupTable->SetTableRange(0,1000);
	//colorLookupTable->SetTableRange(0,250);
	colorLookupTable->SetTableRange(0,200);
//	colorLookupTable->SetTableRange(0,150);
	colorLookupTable->Build();

	// Set mapper
	auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
	mapper->SetInputData(peel[p]);
	//mapper->SetScalarRange(0, 1000);
//	mapper->SetScalarRange(0, 250);
	mapper->SetScalarRange(0, 200);
//	mapper->SetScalarRange(0, 150);
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
	colorLookupTable->SetValueRange(0,1);
	// colorLookupTable->SetTableRange(0,1000);
	// colorLookupTable->SetTableRange(0,250);
	colorLookupTable->SetTableRange(0,200);
//	colorLookupTable->SetTableRange(0,150);
	colorLookupTable->Build();

	// Set mapper
	auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
	mapper->SetInputData(currentPeel);
	// mapper->SetScalarRange(0, 1000);
//	mapper->SetScalarRange(0, 250);
	mapper->SetScalarRange(0, 200);
//	mapper->SetScalarRange(0, 150);
	mapper->SetLookupTable(colorLookupTable);
	mapper->InterpolateScalarsBeforeMappingOn();

	// Set actor
	currentPeelActor->SetMapper(mapper);
	currentPeelActor->GetProperty()->SetBackfaceCulling(1);
	currentPeelActor->GetProperty()->SetOpacity(0.5);
    // currentPeelActor->GetProperty()->SetOpacity(0.25);

	return currentPeelActor;

}

Brain::Brain(char *T1_fname, char *mask_fname) {

	// Read reference image
	std::cout << "Reading T1..." << std::flush;
	auto T1_reader = vtkSmartPointer<vtkNIFTIImageReader>::New();
	T1_reader->SetFileName(T1_fname);
	T1_reader->Update();

	refImage = vtkSmartPointer<vtkImageData>::New();
	refImage = T1_reader->GetOutput();


	// Read for reference surface
	std::cout << "Reading mask..." << std::flush;
	auto mask_reader = vtkSmartPointer<vtkNIFTIImageReader>::New();
	mask_reader->SetFileName(mask_fname);
	mask_reader->Update();

	std::cout << "Done" << std::endl << std::flush;


	std::cout << "Preparing brain surface..." << std::flush;
	auto mc = vtkSmartPointer<vtkContourFilter>::New();
	mc->SetInputConnection(mask_reader->GetOutputPort());
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
	sFormMatrix 						= T1_reader->GetQFormMatrix();
	// sFormMatrix 						= T1_reader->GetSFormMatrix();

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

	std::cout << "Done" << std::endl << std::flush;

	numberOfPeels = 30;
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

vtkSmartPointer<vtkPolyData> readBrain(char *brain_fname) {

	std::cout << "Reading brain mesh... " << std::flush;

	std::string fname = std::string(brain_fname);
	auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
//	auto reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(fname.c_str());
	reader->Update();

	auto surface = vtkSmartPointer<vtkPolyData>::New();
	surface = reader->GetOutput();
//	surface = brain_downsample(surface);


	// Write the file
//	auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
//	writer->SetFileName("100307_right_GM.vtp");
//	writer->SetInputData(surface);
//	writer->Write();

	std::cout<<"Done" << std::endl;

	return surface;

}


vtkSmartPointer<vtkActor> drawBrain(vtkSmartPointer<vtkPolyData> brain) {

	vtkNew<vtkNamedColors> colors;

	// Set mapper
	auto mapper = vtkSmartPointer<vtkOpenGLPolyDataMapper>::New();
	mapper->SetInputData(brain);
	mapper->ScalarVisibilityOff();

	// Set actor
	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	actor->GetProperty()->SetColor(colors->GetColor4d("Pink").GetData());
	actor->GetProperty()->SetOpacity(0.25);
	actor->GetProperty()->SetShading(1);
	actor->GetProperty()->SetSpecular(1);
	actor->GetProperty()->SetSpecularPower(100);
	actor->GetProperty()->SetAmbient(0);
	actor->GetProperty()->SetDiffuse(1);
	actor->GetProperty()->SetSpecularColor(colors->GetColor4d("White").GetData());
	actor->GetProperty()->SetInterpolationToGouraud();
	actor->GetProperty()->SetBackfaceCulling(1);

	return actor;

}
