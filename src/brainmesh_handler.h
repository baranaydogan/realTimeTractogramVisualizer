#ifndef SRC_BRAIN_HANDLER_H_
#define SRC_BRAIN_HANDLER_H_

#include <vtkDecimatePro.h>

#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLDataReader.h>
#include <vtkXMLReader.h>

#include <vtkPolyDataReader.h>

#include <vtkSmartPointer.h>
#include <vtkActor.h>

#include <vtkOpenGLPolyDataMapper.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>

#include <vtkNIFTIImageReader.h>
#include <vtkDiscreteFlyingEdges3D.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkSmoothPolyDataFilter.h>

#include <vtkPolyDataNormals.h>
#include <vtkWarpVector.h>
#include <vtkWarpScalar.h>
#include <vtkCleanPolyData.h>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkImageData.h>
#include <vtkImageReslice.h>
#include <vtkImageBSplineInterpolator.h>
#include <vtkProbeFilter.h>

#include <vtkLinearSubdivisionFilter.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkContourFilter.h>

#include <vtkFillHolesFilter.h>
#include <vtkSurface.h>
#include <vtkIsotropicDiscreteRemeshing.h>

class Brain {
public:
	Brain(std::string T1_fname, std::string mask_fname, void* _rttvis);
	~Brain() { };
	vtkSmartPointer<vtkPolyData>  					refSurface;
	vtkSmartPointer<vtkImageData>					refImage;
	vtkSmartPointer<vtkTransformPolyDataFilter> 	xyz2_refImageSpace;
	vtkSmartPointer<vtkTransformPolyDataFilter> 	refImageSpace2_xyz;

	vtkSmartPointer<vtkPolyData> 					currentPeel;
	vtkSmartPointer<vtkActor> 						currentPeelActor;

	std::vector<vtkSmartPointer<vtkPolyData>>  		peel;
	std::vector<vtkSmartPointer<vtkActor>>  		peelActors;
	int 											currentPeelNo;

	int                                             numberOfPeels;

	vtkSmartPointer<vtkActor> getCurrentPeelActor();
	vtkSmartPointer<vtkActor> getPeelActor(int p);

private:
	void  peelDown();
	void  mapImageOnCurrentPeel();
	void  sliceDown();
	void* rttvis;
};

vtkSmartPointer<vtkPolyData> readBrain(char *brain_fname);
vtkSmartPointer<vtkActor> drawBrain(vtkSmartPointer<vtkPolyData> brain);

vtkSmartPointer<vtkPolyData> readBrainNIFTI(char *T1_fname, char *mask_fname);

#endif
