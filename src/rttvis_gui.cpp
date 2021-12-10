#include "rttvis_gui.h"
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QSpinBox>
#include <QDoubleSpinBox>

RTTVIS::RTTVIS(QMainWindow *parent) : QMainWindow(parent) {

	ui.setupUi(this);

    connect(
        ui.push_T1, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load T1"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_T1_line->setText(tmp);
            fname_T1 = tmp.toStdString();
            }
    );

    connect(
        ui.push_Mask, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load Mask"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_Mask_line->setText(tmp);
            fname_Mask = tmp.toStdString();
            }
    );

    connect(
        ui.push_FOD, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load FOD"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_FOD_line->setText(tmp);
            fname_FOD = tmp.toStdString();
            }
    );

    connect(
        ui.push_ACT, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load ACT"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_ACT_line->setText(tmp);
            fname_ACT = tmp.toStdString();
            }
    );

    connect(
        ui.push_start, 
        &QPushButton::clicked,
        [&](){
            startRealTimeTracker();
            }
    );

    // PARAMETERS

    //Seeding
    connect(
        ui.txt_seed_maxTrials,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->seed_maxTrials(val);
        }
    );

    // Tracking
    connect(
        ui.txt_minLength,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->minLength(val);
            std::cout << "Setting minLength to " << val << std::endl;
        }
    );
    


}

void RTTVIS::startRealTimeTracker()
{

    // Disable push buttons so they can't be run again in this session
    ui.fname_T1_line->setDisabled(true);
    ui.fname_Mask_line->setDisabled(true);
    ui.fname_FOD_line->setDisabled(true);
    ui.fname_ACT_line->setDisabled(true);
    ui.push_T1->setDisabled(true);
    ui.push_Mask->setDisabled(true);
    ui.push_FOD->setDisabled(true);
    ui.push_ACT->setDisabled(true);
    ui.push_start->setDisabled(true);
    ui.FOD_orderOfDirections->setDisabled(true);
    ui.FOD_discretization->setDisabled(true);

    // Prepare brain mesh and peels
	brain = new Brain(fname_T1,fname_Mask);
    
	// Prepare trekker
    std::cout << "Preparing trekker... " << std::endl << std::flush ;

    trekker = new Trekker(fname_FOD, ui.FOD_orderOfDirections->currentText().toStdString(), ui.FOD_discretization->isChecked());
    

    //Seeding
    trekker->seed_maxTrials(1);

	// Tracking
	trekker->minLength(10);
	trekker->maxLength(250);
    trekker->stepSize(0.031250);
    trekker->minRadiusOfCurvature(0.625);
    trekker->dataSupportExponent(0.5);
    trekker->writeInterval(50);
	trekker->atMaxLength("discard");
    trekker->directionality("two_sided");

    // Advanced
    trekker->maxEstInterval(1);
    trekker->initMaxEstTrials(50);
    trekker->propMaxEstTrials(20);
    trekker->maxSamplingPerStep(100);
    trekker->useBestAtInit(false);

	trekker->probeLength(0.15625);
    trekker->probeRadius(0);
    trekker->probeCount(1);
    trekker->probeQuality(3);
    trekker->ignoreWeakLinks(0);


    // Pathway rules
	trekker->pathway_stop_at_entry(fname_ACT,-1);   	  	// outside the brain
    trekker->pathway_discard_if_ends_inside(fname_ACT,1);   // wm
    trekker->pathway_discard_if_enters(fname_ACT,0);        // csf

    trekker->printParameters();
	
    std::cout << std::endl << std::flush ;    
    
    // Prepare user interface
	vtkSmartPointer<vtkTimerCallback> realTimePointer;
	realTimePointer = vtkSmartPointer<vtkTimerCallback>::New();
	realTimePointer->Initialize(brain,trekker,this->getWindowInteractor());
	this->getWindowInteractor()->AddObserver(vtkCommand::TimerEvent, realTimePointer);
	this->getWindowInteractor()->AddObserver(vtkCommand::EndInteractionEvent, realTimePointer);
	this->getWindowInteractor()->AddObserver(vtkCommand::MouseMoveEvent, realTimePointer);
	this->getWindowInteractor()->RemoveObservers(vtkCommand::MouseWheelBackwardEvent);
	this->getWindowInteractor()->AddObserver(vtkCommand::MouseWheelBackwardEvent, realTimePointer);
	this->getWindowInteractor()->RemoveObservers(vtkCommand::MouseWheelForwardEvent);
	this->getWindowInteractor()->AddObserver(vtkCommand::MouseWheelForwardEvent, realTimePointer);
	this->getWindowInteractor()->AddObserver(vtkCommand::KeyPressEvent, realTimePointer);
	this->getWindowInteractor()->CreateRepeatingTimer(10); // Repeats the loop every 1 milliseconds

    // Update parameters in GUI

    // Seeding
    ui.txt_seed_maxTrials->setValue(1);
    
    // Tracking
    ui.txt_minLength->setValue(10);
    ui.txt_maxLength->setValue(250);
    ui.txt_stepSize->setValue(0.03150);
    ui.txt_minRadiusOfCurvature->setValue(0.625);
    ui.txt_dataSupportExponent->setValue(0.5);
    ui.txt_writeInterval->setValue(50);
    ui.txt_atMaxLength->setCurrentText("discard");
    ui.txt_directionality->setCurrentText("two_sided");

    //Advanced
    ui.txt_maxEstInterval->setValue(1);
    ui.txt_initMaxEstTrials->setValue(50);
    ui.txt_propMaxEstTrials->setValue(20);
    ui.txt_maxSamplingPerStep->setValue(100);
    ui.check_useBestAtInit->setChecked(false);

    ui.txt_probeLength->setValue(0.15625);
    ui.txt_probeRadius->setValue(0);
    ui.txt_probeCount->setValue(1);
    ui.txt_probeQuality->setValue(3);
    ui.txt_ignoreWeakLinks->setValue(0);

}
