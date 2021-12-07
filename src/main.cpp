#include "trekker_interface.h"
#include "brainmesh_handler.h"
#include "aux.h"

int main(int argc, char *argv[]) {


	// Prepare brain mesh and peels
	Brain* brain = new Brain(argv[1],argv[2]);

    
	// Prepare trekker
    std::cout << "Preparing trekker... " << std::endl << std::flush ;

    Trekker* trekker = new Trekker(argv[3]);
    
	// Tracking parameters
	// trekker->useBestAtInit(true);
	// trekker->initMaxEstTrials(100);
	// trekker->minLength(10);
	// trekker->maxLength(250);
	// trekker->atMaxLength("discard");
	trekker->seed_maxTrials(1);
	trekker->maxSamplingPerStep(100);
	trekker->stepSize(0.031250);
	trekker->writeInterval(50);
	trekker->minRadiusOfCurvature(0.625);
	trekker->probeLength(0.15625);
	trekker->dataSupportExponent(0.5);
    
    // Pathway rules
	trekker->pathway_stop_at_entry(argv[4],-1);   	  	  // outside the brain
    trekker->pathway_discard_if_ends_inside(argv[4],1);   // wm
    trekker->pathway_discard_if_enters(argv[4],0);        // csf

    trekker->printParameters();
	
    std::cout << std::endl << std::flush ;

    
	// Prepare application window
	QApplication app(argc, argv);
	auto renderer 	= vtkSmartPointer<vtkRenderer>::New();
	RTTVIS_APP* dialog = startRenderer(renderer);
    
    
    // Prepare user interface
	vtkSmartPointer<vtkTimerCallback> realTimePointer;
	realTimePointer = vtkSmartPointer<vtkTimerCallback>::New();
	realTimePointer->Initialize(brain,trekker,dialog->getWindowInteractor());
	dialog->getWindowInteractor()->AddObserver(vtkCommand::TimerEvent, realTimePointer);
	dialog->getWindowInteractor()->AddObserver(vtkCommand::EndInteractionEvent, realTimePointer);
	dialog->getWindowInteractor()->AddObserver(vtkCommand::MouseMoveEvent, realTimePointer);
	dialog->getWindowInteractor()->RemoveObservers(vtkCommand::MouseWheelBackwardEvent);
	dialog->getWindowInteractor()->AddObserver(vtkCommand::MouseWheelBackwardEvent, realTimePointer);
	dialog->getWindowInteractor()->RemoveObservers(vtkCommand::MouseWheelForwardEvent);
	dialog->getWindowInteractor()->AddObserver(vtkCommand::MouseWheelForwardEvent, realTimePointer);
	dialog->getWindowInteractor()->AddObserver(vtkCommand::KeyPressEvent, realTimePointer);
	dialog->getWindowInteractor()->CreateRepeatingTimer(10); // Repeats the loop every 1 milliseconds
    
    
    // Run application
	app.exec();

    
	// Clean up
	realTimePointer->Destroy();
	delete trekker;
	delete brain;
	delete dialog;

	return EXIT_SUCCESS;
}
