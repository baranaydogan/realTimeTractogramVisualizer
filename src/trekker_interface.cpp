#include "trekker_interface.h"
#include "aux.h"
#include "rttvis_gui.h"

namespace MULTITHREADER {
std::condition_variable  exit_cv;
std::mutex               exit_mx;
std::mutex               tracker_lock;
}

vtkSmartPointer<vtkActor> getTrkActor(std::vector<Coordinate> trk, TrkColor* trkColor, int* cycle) {

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
            actor->GetProperty()->SetOpacity(0.008264463*double(*cycle)*double(*cycle));

		}


		// Create tube
		auto tubeFilter = vtkSmartPointer<vtkTubeFilter>::New();
		tubeFilter->SetRadius(0.5);
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
            actor->GetProperty()->SetOpacity(0.008264463*double(*cycle)*double(*cycle));
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

void getStreamlineForROC(TrackerWithActor *trackerWithActor) {
    trackerWithActor->tracker->track(trackerWithActor->seed);
	if (trackerWithActor->tracker->streamline->status==STREAMLINE_GOOD)
    	*trackerWithActor->actor = getTrkActor(trackerWithActor->tracker->streamline->coordinates,trackerWithActor->trkColor,trackerWithActor->cycle);
	else
		*trackerWithActor->actor = NULL;

}


void getTrkActorsInParallel(Coordinate* seed,int nthreads, vtkSmartPointer<vtkActor>* actors, TrkColor* trkColor, TrackingThread* tracker,int* cycle) {
    
	int seedNo;
    
    RandomDoer randomThings;
    float      radius = 1;
    
    std::thread trekkers[nthreads];
    
	for(seedNo=0; seedNo<nthreads; seedNo++){
        
        Coordinate* randomlyMovedSeed       = new Coordinate();
        randomlyMovedSeed->x                = seed->x + radius*randomThings.uniform_m05_p05();
        randomlyMovedSeed->y                = seed->y + radius*randomThings.uniform_m05_p05();
        randomlyMovedSeed->z                = seed->z + radius*randomThings.uniform_m05_p05();

        tracker[seedNo].updateSeedNoAndTrialCount(seedNo,0);
        
		TrackerWithActor* trackerWithActor 	= new TrackerWithActor;
		trackerWithActor->seed 				= randomlyMovedSeed;
		trackerWithActor->tracker 			= tracker+seedNo;
		trackerWithActor->actor 			= &(actors[seedNo]);
		trackerWithActor->trkColor 			= trkColor;
        trackerWithActor->cycle 		    = cycle;

        trekkers[seedNo] =  std::thread(getStreamlineForROC, trackerWithActor);

		trackerWithActor = NULL;
	}
	
	for(seedNo=0; seedNo<nthreads; seedNo++){
        trekkers[seedNo].join();
    }

}


void vtkTimerCallback::Initialize(
		Brain*   _brain,
        Trekker* _trekker,
		void*  	 _rttvis) {



	std::cout << "Initializing viewer..." << std::flush;

	picker 				= vtkSmartPointer<vtkCellPicker>::New();
	picker->InitializePickList();
	interactor 			= static_cast<RTTVIS*>(_rttvis)->getWindowInteractor();

	// Setup brain
	brain 				= _brain;


	peelNo 				= 0;
	brainPolyData 		= brain->peel[peelNo];
	brainActor 			= brain->getPeelActor(peelNo);
	picker->AddPickList(brainActor);
	picker->SetPickFromList(1);

	interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(brainActor);
	interactor->GetRenderWindow()->Render();
    
    // Setup seed addSphere
    seedSphere          = vtkSmartPointer<vtkActor>::New();
    
	// Setup trekker
    trekker             = _trekker;
	currentlyShown 		= 0;
    cycleCounter        = 0;
	maxAllowedToShow 	= 4000;

	nthreads 	= 100;
	tmpactors 	= new vtkSmartPointer<vtkActor>[nthreads];
	tracker 	= new TrackingThread[nthreads];
    
	trkColor 	             = SEGMENTDIRECTION;
    visualizeUncertainty     = true;

	std::cout << "Done" << std::endl << std::flush;

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
        
        // if ((cellId!=-1) && (currentlyShown!=maxAllowedToShow)) {

            if (currentlyShown>=maxAllowedToShow) {
                for (int n=0; n<nthreads; n++) {
                    if (trackActors[0])
                        interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(trackActors[0]);
                    trackActors.erase(trackActors.begin());
                }
                currentlyShown -= nthreads;
            }

            Coordinate *seed = new Coordinate(picked[0],picked[1],picked[2]);
            
            addSphere(picked,seedSphere);
    
            
            
            // Update tracking parameters
            
            cycleCounter++;
            
            // Test fixed
            // trekker->minFODamp(0.05);
            // trekker->minFODamp(0.1);
            // trekker->probeLength(0.1);
            
            // Test varying
            trekker->minFODamp(0.0090909091*double(cycleCounter));
			// std::cout << "minFODamp: " << 0.0090909091*double(cycleCounter) << std::endl << std::flush;
            // trekker->minFODamp(0.0090909091*double(cycleCounter)/2.0);
            // trekker->probeLength(0.0090909091*double(cycleCounter));
            // trekker->stepSize(0.11 - 0.0090909091*double(cycleCounter));
            

            int cycle;
            if (visualizeUncertainty)
                cycle = cycleCounter;
            else
                cycle = 11;
            
            getTrkActorsInParallel(seed,nthreads,tmpactors,&trkColor,tracker,&cycle);
            
            if (cycleCounter==11) cycleCounter=0;
            
            
            for (int n=0; n<nthreads; n++) {
                trackActors.push_back(tmpactors[n]);
                interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(tmpactors[n]);
            }
            currentlyShown += nthreads;
            
            /*
            if (currentlyShown==maxAllowedToShow)
                std::cout<<"Reached max"<<std::endl<<std::flush;
            */
            

            
            interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(seedSphere);
            
            delete seed;

        }
        interactor->GetRenderWindow()->Render();
        
	
	}
	break;


	case vtkCommand::MouseMoveEvent:
	case vtkCommand::EndInteractionEvent:
	{
        for(vtkIdType i=0; i<currentlyShown; i++)
            interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(trackActors[i]);
        
        interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(seedSphere);
        
        if (trackActors.size()) trackActors.clear();
        
        cycleCounter=0;
        currentlyShown=0;
        
	}
	break;


	case vtkCommand::MouseWheelForwardEvent:
	{

		if (peelNo<brain->numberOfPeels) {
			peelNo++;
			// std::cout << "Slicing down to peel: " << peelNo << std::endl << std::flush;
			updatePeel();
		}

	}
	break;

	case vtkCommand::MouseWheelBackwardEvent:
	{

		if (peelNo>0) {
			peelNo--;
			// std::cout << "Slicing up to peel: " << peelNo << std::endl << std::flush;
			updatePeel();
		}

	}
	break;


	case vtkCommand::KeyPressEvent:
	{

		std::string key = interactor->GetKeySym();

		if (key=="c") {
			if (trkColor==WHITE)
				trkColor=UNCERTAINTY;
			else if (trkColor==UNCERTAINTY)
				trkColor=SEGMENTDIRECTION;
			else if (trkColor==SEGMENTDIRECTION)
				trkColor=WHITE;
		}
		
		if (key=="u")
			visualizeUncertainty = !visualizeUncertainty;
        
        if (key=="d") {
			visualizeUncertainty = false;
            trekker->minFODamp(0.1);
            trekker->probeLength(0.1);
            trekker->stepSize(0.01);
            trekker->writeInterval(200);
        }
		
        if (key=="p") {
			visualizeUncertainty = false;
            trekker->minFODamp(0.01);
            trekker->probeLength(0.01);
            trekker->stepSize(0.1);
            trekker->writeInterval(20);
        }
		
		interactor->InvokeEvent(vtkCommand::EndInteractionEvent);

	}
	break;


	}

}
