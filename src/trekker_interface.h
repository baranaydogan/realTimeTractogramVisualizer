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

// For real time fiber tracking
class vtkTimerCallback : public vtkCommand {

public:

	static vtkTimerCallback *New() {
		vtkTimerCallback *cb = new vtkTimerCallback;
		cb->TimerCount = 0;
		return cb;
	}

	Brain* 										brain;
	int											peelNo;

	vtkSmartPointer<vtkPolyData> 				brainPolyData;
	vtkSmartPointer<vtkActor> 					brainActor;
    vtkSmartPointer<vtkActor> 					seedSphere;
    
    
	vtkSmartPointer<vtkCellPicker> 				picker;
	std::vector<vtkSmartPointer<vtkActor>> 		trackActors;

	vtkSmartPointer<vtkRenderWindowInteractor>  interactor;

	int  currentlyShown;
	int  maxAllowedToShow;
	int  batchSize;
    bool visualizeUncertainty;

	bool initializationFlag;

    int  cycleCounter;
	int  timerId;
    
    Trekker*                    trekker;
    
	vtkSmartPointer<vtkActor>*  tmpactors;
	TrackingThread* 			tracker;

	TrkColor					trkColor;

	float seedRadius   = 1;
	float tubeRadius   = 0.5;
	float addedOpacity = 0;


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

	void setMaxShown(int _maxAllowedToShow) {maxAllowedToShow = _maxAllowedToShow;}

	void setBatchSize(int _batchSize) {
		Destroy();
		batchSize 	= _batchSize;
		tmpactors 	= new vtkSmartPointer<vtkActor>[batchSize];
		tracker 	= new TrackingThread[batchSize];
	}

	void setSeedRadius(float _seedRadius) {seedRadius=_seedRadius;}
	void setTubeRadius(float _tubeRadius) {tubeRadius=_tubeRadius;}
	void setAddedOpacity(float _addedOpacity) {addedOpacity=_addedOpacity;}
	void setUncertainty(bool _uncertainty) {visualizeUncertainty=_uncertainty;}
    

private:
	int 	TimerCount;
	void* 	rttvis;
	bool    paused;
	bool    fixed;

};



#endif
