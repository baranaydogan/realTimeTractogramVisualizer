#include "aux.h"

void addSphere(double *picked, vtkSmartPointer<vtkActor> actor, float sradius) {

	vtkNew<vtkNamedColors> colors;

	auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(picked[0], picked[1], picked[2]);
	sphereSource->SetRadius(sradius+1.0);

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor4d("Red").GetData());
	actor->GetProperty()->ShadingOn();
	actor->GetProperty()->SetInterpolationToPhong();
	actor->GetProperty()->SetShading(1);
	actor->GetProperty()->SetOpacity(1);
}

RTTVIS* startRenderer(vtkSmartPointer<vtkRenderer> renderer) {

	// Prep light
	auto light = vtkSmartPointer<vtkLightKit>::New();
	light->AddLightsToRenderer(renderer);
	light->SetKeyLightIntensity(1);
//	light->SetKeyToFillRatio(1);
	renderer->LightFollowCameraOn();


	vtkNew<vtkNamedColors> colors;
	renderer->SetBackground(colors->GetColor3d("Black").GetData());
	renderer->SetUseFXAA(1); // Anti-aliasing


	// Prep window
	auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	window->AddRenderer(renderer);

	RTTVIS* dialog = new RTTVIS;

	dialog->addWindow(window);
	dialog->show();

	return dialog;
}
