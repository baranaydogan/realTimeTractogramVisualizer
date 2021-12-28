#include "trekker_interface.h"
#include "aux.h"
#include "rttvis_gui.h"
#include <string>
#include <utility>
#include <tuple>
#include <sstream>
#include <iomanip>

namespace MULTITHREADER {
std::condition_variable  exit_cv;
std::mutex               exit_mx;
std::mutex               tracker_lock;
}

vtkSmartPointer<vtkActor> getTrkActor(std::vector<Coordinate> trk, TrkColor* trkColor, int* cycle, float tradius, float addAlpha) {

	// Set actor
	auto actor = vtkSmartPointer<vtkActor>::New();

	int numberOfPoints = trk.size();

	if (numberOfPoints>2) {

		// Make a line
		auto points = vtkSmartPointer<vtkPoints>::New();
		for (int i=0; i<numberOfPoints; i++ ) {
			double p[3] = {trk[i].x,trk[i].y,trk[i].z};
			points->InsertNextPoint(p);
		}

		auto line = vtkSmartPointer<vtkPolyLine>::New();
		line->GetPointIds()->SetNumberOfIds(numberOfPoints);
		for(unsigned int i = 0; i < numberOfPoints; i++)
			line->GetPointIds()->SetId(i,i);

		auto lines = vtkSmartPointer<vtkCellArray>::New();
		lines->InsertNextCell(line);

		auto linesPolyData = vtkSmartPointer<vtkPolyData>::New();
		linesPolyData->SetPoints(points);
		linesPolyData->SetLines(lines);


		if (*trkColor == SEGMENTDIRECTION) {

			auto segmentColors = vtkSmartPointer<vtkUnsignedCharArray>::New();
			segmentColors->SetNumberOfComponents(3);

			Coordinate direction;

			unsigned char* segmentColor = new unsigned char[3];
			for (int i=0; i<(numberOfPoints-1); i++ ) {
				direction = trk[i+1]-trk[i];
				direction.normalize();

				segmentColor[0] = (fabs(direction.x))*255;
				segmentColor[1] = (fabs(direction.y))*255;
				segmentColor[2] = (fabs(direction.z))*255;

				segmentColors->InsertNextTypedTuple(segmentColor);
			}
			segmentColors->InsertNextTypedTuple(segmentColor);
			linesPolyData->GetPointData()->SetScalars(segmentColors);
            actor->GetProperty()->SetOpacity(0.008264463*double(*cycle)*double(*cycle)+addAlpha);

		}


		// Create tube
		auto tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
		tubeFilter->SetRadius(tradius);
		tubeFilter->SetNumberOfSides(6);
		tubeFilter->SetInputData(linesPolyData);
		tubeFilter->Update();

		// Set mapper
		auto mapper 	= vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(tubeFilter->GetOutput());

		actor->SetMapper(mapper);


		vtkNew<vtkNamedColors> colors;
		if (*trkColor == WHITE) {
			actor->GetProperty()->SetColor(colors->GetColor4d("White").GetData());
            actor->GetProperty()->SetOpacity(0.008264463*double(*cycle)*double(*cycle)+addAlpha);
        }
        
		if (*trkColor == UNCERTAINTY) {            
            if (*cycle==1)  actor->GetProperty()->SetColor(0.25 ,0    ,0);
            if (*cycle==2)  actor->GetProperty()->SetColor(0.5  ,0    ,0);
            if (*cycle==3)  actor->GetProperty()->SetColor(0.75 ,0    ,0);
            if (*cycle==4)  actor->GetProperty()->SetColor(1    ,0    ,0);
            if (*cycle==5)  actor->GetProperty()->SetColor(1    ,0.25 ,0);
            if (*cycle==6)  actor->GetProperty()->SetColor(1    ,0.5  ,0);
            if (*cycle==7)  actor->GetProperty()->SetColor(1    ,0.75 ,0);
            if (*cycle==8)  actor->GetProperty()->SetColor(1    ,1    ,0);
            if (*cycle==9)  actor->GetProperty()->SetColor(1    ,1    ,0.33);
            if (*cycle==10) actor->GetProperty()->SetColor(1    ,1    ,0.66);
            if (*cycle==11) actor->GetProperty()->SetColor(1    ,1    ,1);
            
        }        
        
		actor->GetProperty()->SetShading(1);
		actor->GetProperty()->SetSpecular(1);
		actor->GetProperty()->SetSpecularPower(100);
		actor->GetProperty()->SetAmbient(0);
		actor->GetProperty()->SetDiffuse(1);
		actor->GetProperty()->SetSpecularColor(colors->GetColor4d("White").GetData());
		actor->GetProperty()->SetInterpolationToGouraud();
        
        return actor;

	}
	else
        return NULL;

}

void getStreamlineForROC(std::tuple<TrackerWithActor*, float, float> params) {

	TrackerWithActor *trackerWithActor  = std::get<0>(params);
	float tradius 						= std::get<1>(params);
	float addAlpha 						= std::get<2>(params);

    trackerWithActor->tracker->track(trackerWithActor->seed);
	if (trackerWithActor->tracker->streamline->status==STREAMLINE_GOOD)
    	*trackerWithActor->actor = getTrkActor(trackerWithActor->tracker->streamline->coordinates,trackerWithActor->trkColor,trackerWithActor->cycle, tradius, addAlpha);
	else
		*trackerWithActor->actor = NULL;

}


void getTrkActorsInParallel(Coordinate* seed,int batchSize, vtkSmartPointer<vtkActor>* actors, TrkColor* trkColor, TrackingThread* tracker,int* cycle,float sradius,float tradius,float addAlpha) {
    
	int seedNo;
    
    RandomDoer randomThings;
    
    std::thread trekkers[batchSize];
    
	for(seedNo=0; seedNo<batchSize; seedNo++){
        
        Coordinate* randomlyMovedSeed       = new Coordinate();
        randomlyMovedSeed->x                = seed->x + sradius*randomThings.uniform_m05_p05();
        randomlyMovedSeed->y                = seed->y + sradius*randomThings.uniform_m05_p05();
        randomlyMovedSeed->z                = seed->z + sradius*randomThings.uniform_m05_p05();

        tracker[seedNo].updateSeedNoAndTrialCount(seedNo,0);
        
		TrackerWithActor* trackerWithActor 	= new TrackerWithActor;
		trackerWithActor->seed 				= randomlyMovedSeed;
		trackerWithActor->tracker 			= tracker+seedNo;
		trackerWithActor->actor 			= &(actors[seedNo]);
		trackerWithActor->trkColor 			= trkColor;
        trackerWithActor->cycle 		    = cycle;

		std::tuple<TrackerWithActor*, float, float> params(trackerWithActor,tradius,addAlpha);

        trekkers[seedNo] =  std::thread(getStreamlineForROC,params);

		trackerWithActor = NULL;
	}
	
	for(seedNo=0; seedNo<batchSize; seedNo++){
        trekkers[seedNo].join();
    }

}


void vtkTimerCallback::Initialize(
		Brain*   _brain,
        Trekker* _trekker,
		void*  	 _rttvis) {

	picker 				= vtkSmartPointer<vtkCellPicker>::New();
	picker->InitializePickList();
	rttvis              = _rttvis;
	RTTVIS* rtt         = static_cast<RTTVIS*>(rttvis);
	interactor 			= rtt->getWindowInteractor();

	// Setup seed addSphere
    seedSphere          = vtkSmartPointer<vtkActor>::New();

	// Setup brain
	brain 				= _brain;
	peelNo 				= 12;
	brainPolyData 		= brain->peel[peelNo];
	brainActor 			= brain->getPeelActor(peelNo);
	picker->AddPickList(brainActor);
	picker->SetPickFromList(1);

    interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(seedSphere);
	interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(brainActor);
	interactor->GetRenderWindow()->Render();
    
	// Setup trekker
    trekker             = _trekker;
	currentlyShown 		= 0;
    cycleCounter        = 0;
	maxAllowedToShow 	= 1000;

	batchSize 	= 100;
	tmpactors 	= new vtkSmartPointer<vtkActor>[batchSize];
	tracker 	= new TrackingThread[batchSize];
    
	trkColor 	             = SEGMENTDIRECTION;
    visualizeUncertainty     = true;

	interactor->AddObserver(vtkCommand::TimerEvent, this);
	interactor->AddObserver(vtkCommand::LeftButtonPressEvent, this);
	interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, this);
	// interactor->AddObserver(vtkCommand::EndInteractionEvent, this);
	interactor->AddObserver(vtkCommand::MouseMoveEvent, this);
	interactor->RemoveObservers(vtkCommand::MouseWheelBackwardEvent);
	interactor->AddObserver(vtkCommand::MouseWheelBackwardEvent, this);
	interactor->RemoveObservers(vtkCommand::MouseWheelForwardEvent);
	interactor->AddObserver(vtkCommand::MouseWheelForwardEvent, this);
	interactor->RemoveObservers(vtkCommand::CharEvent);
	interactor->AddObserver(vtkCommand::KeyPressEvent, this);

	timerId = interactor->CreateRepeatingTimer(10);
	paused  = false;

	interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
	interactor->InvokeEvent(vtkCommand::LeftButtonPressEvent);
	interactor->InvokeEvent(vtkCommand::LeftButtonReleaseEvent);

	// Update info
    rtt->ui.txt_info->setText("Press 'p' to pause");

	return;

}


void vtkTimerCallback::updatePeel() {
	picker->DeletePickList(brainActor);

	interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(brainActor);

	brainPolyData 		= brain->peel[peelNo];
	brainActor 			= brain->getPeelActor(peelNo);

	picker->AddPickList(brainActor);

	interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(brainActor);
	interactor->GetRenderWindow()->Render();
}


void vtkTimerCallback::Execute(vtkObject*, unsigned long event, void *vtkNotUsed(calldata)) {
    
	switch (event) {

	case vtkCommand::TimerEvent:
	{
        
        picker->Pick(
                interactor->GetEventPosition()[0],
                interactor->GetEventPosition()[1],
                0,
                interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

        double* picked 		= picker->GetPickPosition();
        vtkIdType cellId 	= picker->GetCellId();
    
        if (cellId!=-1) {

            if (currentlyShown>=maxAllowedToShow) {
                for (int n=0; n<batchSize; n++) {
                    if (trackActors[0])
                        interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(trackActors[0]);
                    trackActors.erase(trackActors.begin());
                }
                currentlyShown -= batchSize;
            }

			// Get seed
            Coordinate *seed = new Coordinate(picked[0],picked[1],picked[2]);

			// Print coordinates
			RTTVIS* rtt	= static_cast<RTTVIS*>(rttvis);
			std::stringstream ss;
			ss << std::setprecision(4);
			ss << picked[0] << " " << picked[1] << " " << picked[2];
			rtt->ui.txt_coordinates->setText(QString::fromStdString(ss.str()));

			// Show seed actor
			addSphere(picked,seedSphere,seedRadius);
            interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(seedSphere);
            
            // Update tracking parameters with varying minFODamp
            cycleCounter++;
            trekker->minFODamp(0.0090909091*double(cycleCounter));
            
            int cycle = (visualizeUncertainty) ? cycleCounter : 11;
            
            getTrkActorsInParallel(seed,batchSize,tmpactors,&trkColor,tracker,&cycle,seedRadius,tubeRadius,addedOpacity);
            
            if (cycleCounter==11) cycleCounter=0;
            
            for (int n=0; n<batchSize; n++) {
                trackActors.push_back(tmpactors[n]);
                interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(tmpactors[n]);
            }
            currentlyShown += batchSize;

			interactor->GetRenderWindow()->Render();
            
            delete seed;

        }
        
	
	}
	break;


	case vtkCommand::MouseMoveEvent:
	{
		if (!paused) {
			for(vtkIdType i=0; i<currentlyShown; i++)
				interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(trackActors[i]);
			
			interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(seedSphere);
			
			if (trackActors.size()) trackActors.clear();
			
			cycleCounter=0;
			currentlyShown=0;
		}
        
	}
	break;


	case vtkCommand::MouseWheelForwardEvent:
	{

		RTTVIS* rtt = static_cast<RTTVIS*>(rttvis);

		if (peelNo<brain->numberOfPeels) {
			peelNo++;
			rtt->ui.txt_peelNo->setValue(peelNo);
			updatePeel();
		}

	}
	break;

	case vtkCommand::MouseWheelBackwardEvent:
	{

		RTTVIS* rtt = static_cast<RTTVIS*>(rttvis);

		if (peelNo>0) {
			peelNo--;
			rtt->ui.txt_peelNo->setValue(peelNo);
			updatePeel();
		}

	}
	break;


	case vtkCommand::KeyPressEvent:
	{

		std::string key = interactor->GetKeySym();

		if (key=="r") {
			interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
			interactor->InvokeEvent(vtkCommand::LeftButtonPressEvent);
			interactor->InvokeEvent(vtkCommand::LeftButtonReleaseEvent);
		}

		if (key=="c") {

			if (trkColor==WHITE)
				trkColor=UNCERTAINTY;
			else if (trkColor==UNCERTAINTY)
				trkColor=SEGMENTDIRECTION;
			else if (trkColor==SEGMENTDIRECTION)
				trkColor=WHITE;

			interactor->InvokeEvent(vtkCommand::MouseMoveEvent);
		}
		
		if (key=="u") {

			visualizeUncertainty = !visualizeUncertainty;

			interactor->InvokeEvent(vtkCommand::MouseMoveEvent);

		}

		if (key=="p") {

			RTTVIS* rtt = static_cast<RTTVIS*>(rttvis);

			if (paused) {
				timerId = interactor->CreateRepeatingTimer(10);
				rtt->ui.txt_info->setText("Press 'p' to pause");
			}
			else {
				interactor->DestroyTimer(timerId);
				rtt->ui.txt_info->setText("Press 'p' to resume");
			}

			paused = !paused;
        }

	}
	break;


	}

}
