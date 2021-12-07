#include "aux.h"

void addSphere(double *picked, vtkSmartPointer<vtkActor> actor) {

	vtkNew<vtkNamedColors> colors;

	auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(picked[0], picked[1], picked[2]);
	sphereSource->SetRadius(2.0);

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor4d("Red").GetData());
	actor->GetProperty()->ShadingOn();
	actor->GetProperty()->SetInterpolationToPhong();
	actor->GetProperty()->SetShading(1);
	actor->GetProperty()->SetOpacity(1);
}

RTTVIS_APP* startRenderer(vtkSmartPointer<vtkRenderer> renderer) {

	// Prep light
	auto light = vtkSmartPointer<vtkLightKit>::New();
	light->AddLightsToRenderer(renderer);
	light->SetKeyLightIntensity(1);
//	light->SetKeyToFillRatio(1);
	renderer->LightFollowCameraOn();


	vtkNew<vtkNamedColors> colors;
	renderer->SetBackground(colors->GetColor3d("Black").GetData());
	renderer->SetUseFXAA(1); // Anti-aliasing

//	renderer->GetRenderWindow()->SetAlphaBitPlanes(1);
//	renderer->GetRenderWindow()->SetMultiSamples(0);
//	renderer->SetUseDepthPeeling(1);
//	renderer->SetUseDepthPeelingForVolumes(1);
//	renderer->SetUseHiddenLineRemoval(1);


	// Ospray
	// vtkOSPRayRendererNode::SetRendererType("pathtracer", renderer);
	// vtkOSPRayRendererNode::SetSamplesPerPixel(40,renderer);

	// vtkOSPRayRendererNode::SetRendererType("scivis", renderer);
	// vtkOSPRayLightNode::SetLightScale(1.5);
    
	// auto ospray = vtkSmartPointer<vtkOSPRayPass>::New();
	// renderer->SetUseShadows(1);
	// renderer->SetPass(ospray);


	// OptiX
	// auto optix = vtkSmartPointer<vtkOptiXPass>::New();
	// renderer->SetUseShadows(1);
	// renderer->SetPass(optix);



	// Prep window
	auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	window->AddRenderer(renderer);

	RTTVIS_APP* dialog = new RTTVIS_APP;

	dialog->addWindow(window);
	dialog->show();

	return dialog;
}