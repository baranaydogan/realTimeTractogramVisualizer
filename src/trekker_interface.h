#ifndef SRC_TREKKER_INTERFACE_H_
#define SRC_TREKKER_INTERFACE_H_

#include "trekker.h"
#include "tracker/tracker_thread.h"
#include "math/doRandomThings.h"

#include <iostream>
#include <string>
#include <cstring>

#include <thread>
#include <semaphore.h>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkPolyData.h>
#include <vtkTubeFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

#include <vtkCellPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include "brainmesh_handler.h"

typedef enum {
	WHITE,
	UNCERTAINTY,
	SEGMENTDIRECTION
} TrkColor;

struct TrackerWithActor {
	Coordinate* 				seed;
	TrackingThread* 			tracker;
	vtkSmartPointer<vtkActor>*  actor;
	TrkColor* 					trkColor;
    int*                        cycle;
};


vtkSmartPointer<vtkActor> getTrkActor(std::vector<Coordinate> trk);
void getStreamlineForROC(TrackerWithActor *trackerWithActor);
void getTrkActorsInParallel(Coordinate* seed,int nthreads,vtkSmartPointer<vtkActor>* actors, TrackingThread* tracker,int* cycle);


// For real time fiber tracking
class vtkTimerCallback : public vtkCommand {

public:

	static vtkTimerCallback *New() {
		vtkTimerCallback *cb = new vtkTimerCallback;
		cb->TimerCount = 0;
		return cb;
	}

	Brain* 									brain;
	int										peelNo;

	vtkSmartPointer<vtkPolyData> 			brainPolyData;
	vtkSmartPointer<vtkActor> 				brainActor;
    vtkSmartPointer<vtkActor> 				seedSphere;
    
    
	vtkSmartPointer<vtkCellPicker> 			picker;
	std::vector<vtkSmartPointer<vtkActor>> 	trackActors;

	vtkSmartPointer<vtkRenderWindowInteractor>  interactor;

	int 						currentlyShown;
	int 						maxAllowedToShow;
    bool                        visualizeUncertainty;

	bool initializationFlag;

    int cycleCounter;
	int nthreads;
    
    Trekker*                    trekker;
    
	vtkSmartPointer<vtkActor>*  tmpactors;
	TrackingThread* 			tracker;

	TrkColor					trkColor;


	void Initialize(
			Brain* 		_brain,
            Trekker*    _trekker,
			void* 		_rttvis);

	void Destroy() {
		delete[] tmpactors;
		delete[] tracker;
	}

	virtual void Execute(vtkObject*, unsigned long event, void *vtkNotUsed(calldata));

	void updatePeel();
    

private:
	int TimerCount;

};



#endif
