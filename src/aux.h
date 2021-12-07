#ifndef SRC_AUX_H_
#define SRC_AUX_H_

#include "rttvis_app.h"

#include <vtkLightKit.h>

// #include <vtkOSPRayPass.h>
// #include <vtkOSPRayRendererNode.h>
// #include <vtkOSPRayLightNode.h>


// #include <vtkOptiXRendererNode.h>
// #include <vtkOptiXPass.h>


#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

void addSphere(double *picked, vtkSmartPointer<vtkActor> actor);
RTTVIS_APP* startRenderer(vtkSmartPointer<vtkRenderer> renderer);

#endif
