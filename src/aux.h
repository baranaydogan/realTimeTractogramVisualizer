#ifndef SRC_AUX_H_
#define SRC_AUX_H_

#include "rttvis_gui.h"

#include <vtkLightKit.h>

// Enable for OSRay
// #include <vtkOSPRayPass.h>
// #include <vtkOSPRayRendererNode.h>
// #include <vtkOSPRayLightNode.h>

// Enable for OptiX
// #include <vtkOptiXRendererNode.h>
// #include <vtkOptiXPass.h>


#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

void addSphere(double *picked, vtkSmartPointer<vtkActor> actor, float sradius);

RTTVIS* startRenderer(vtkSmartPointer<vtkRenderer> renderer);

#endif
