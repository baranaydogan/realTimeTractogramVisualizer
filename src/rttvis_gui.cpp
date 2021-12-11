#include "rttvis_gui.h"
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <qcheckbox.h>
#include <qcombobox.h>

RTTVIS::RTTVIS(QMainWindow *parent) : QMainWindow(parent) {

	ui.setupUi(this);

    connect(
        ui.push_T1, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load T1"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_T1_line->setText(tmp);
            fname_T1 = tmp.toStdString();
            if ((ui.fname_T1_line->text()!="N/A") && (ui.fname_Mask_line->text()!="N/A") && (ui.fname_FOD_line->text()!="N/A") && (ui.fname_ACT_line->text()!="N/A")) {
                ui.StartTracker->setEnabled(true);
            }
        }

    );

    connect(
        ui.push_Mask, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load Mask"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_Mask_line->setText(tmp);
            fname_Mask = tmp.toStdString();
            if ((ui.fname_T1_line->text()!="N/A") && (ui.fname_Mask_line->text()!="N/A") && (ui.fname_FOD_line->text()!="N/A") && (ui.fname_ACT_line->text()!="N/A")) {
                ui.StartTracker->setEnabled(true);
            }
        }
    );

    connect(
        ui.push_FOD, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load FOD"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_FOD_line->setText(tmp);
            fname_FOD = tmp.toStdString();
            if ((ui.fname_T1_line->text()!="N/A") && (ui.fname_Mask_line->text()!="N/A") && (ui.fname_FOD_line->text()!="N/A") && (ui.fname_ACT_line->text()!="N/A")) {
                ui.StartTracker->setEnabled(true);
            }
        }
    );

    connect(
        ui.push_ACT, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load ACT"), "", tr("Nifti image (*.nii *.nii.gz)"));
            ui.fname_ACT_line->setText(tmp);
            fname_ACT = tmp.toStdString();
            if ((ui.fname_T1_line->text()!="N/A") && (ui.fname_Mask_line->text()!="N/A") && (ui.fname_FOD_line->text()!="N/A") && (ui.fname_ACT_line->text()!="N/A")) {
                ui.StartTracker->setEnabled(true);
            }
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
            // std::cout << "minLength: " << val << std::endl;
        }
    );

    connect(
        ui.txt_maxLength,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->maxLength(val);
            // std::cout << "maxLength: " << val << std::endl;
        }
    );

    connect(
        ui.txt_stepSize,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->stepSize(val);
            // std::cout << "stepSize: " << val << std::endl;
        }
    );

    connect(
        ui.txt_minRadiusOfCurvature,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->minRadiusOfCurvature(val);
            // std::cout << "minRadiusOfCurvature: " << val << std::endl;
        }
    );

    connect(
        ui.txt_dataSupportExponent,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->dataSupportExponent(val);
            // std::cout << "dataSupportExponent: " << val << std::endl;
        }
    );

    connect(
        ui.txt_writeInterval,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->writeInterval(val);
            // std::cout << "writeInterval: " << val << std::endl;
        }
    );

    connect(
        ui.txt_atMaxLength,
        QOverload<const QString&>::of(&QComboBox::currentTextChanged),
        [&](const QString& val){
            if (val=="atMaxLength") {
                trekker->atMaxLength("discard");
                // std::cout << "atMaxLength: discard" << std::endl;
                ui.txt_atMaxLength->setCurrentText("discard");
            } else {
                trekker->atMaxLength(val.toStdString());
                // std::cout << "atMaxLength: " << val.toStdString() << std::endl;
            }
        }
    );
    
    connect(
        ui.txt_directionality,
        QOverload<const QString&>::of(&QComboBox::currentTextChanged),
        [&](const QString& val){
            if (val=="directionality") {
                trekker->directionality("two_sided");
                // std::cout << "directionality: two_sided" << std::endl;
                ui.txt_directionality->setCurrentText("two_sided");
            } else {
                trekker->directionality(val.toStdString());
                // std::cout << "directionality: " << val.toStdString() << std::endl;
            }
        }
    );

    //Advanced
    connect(
        ui.txt_maxEstInterval,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->maxEstInterval(val);
            // std::cout << "maxEstInterval: " << val << std::endl;
        }
    );

    connect(
        ui.txt_initMaxEstTrials,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->initMaxEstTrials(val);
            // std::cout << "initMaxEstTrials: " << val << std::endl;
        }
    );

    connect(
        ui.txt_propMaxEstTrials,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->propMaxEstTrials(val);
            // std::cout << "propMaxEstTrials: " << val << std::endl;
        }
    );

    connect(
        ui.txt_maxSamplingPerStep,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->maxSamplingPerStep(val);
            // std::cout << "maxSamplingPerStep: " << val << std::endl;
        }
    );

    connect(
        ui.check_useBestAtInit,
        QOverload<int>::of(&QCheckBox::stateChanged),
        [&](int val){
            if (val==0) {
                trekker->useBestAtInit(false);
                // std::cout << "useBestAtInit: false" << std::endl;
            } else {
                trekker->useBestAtInit(false);
                // std::cout << "useBestAtInit: true" << std::endl;
            }
                
        }
    );

    connect(
        ui.txt_probeLength,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->probeLength(val);
            // std::cout << "probeLength: " << val << std::endl;
        }
    );

    connect(
        ui.txt_probeRadius,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->probeRadius(val);
            // std::cout << "probeRadius: " << val << std::endl;
        }
    );

    connect(
        ui.txt_probeCount,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->probeCount(val);
            // std::cout << "probeCount: " << val << std::endl;
        }
    );

    connect(
        ui.txt_probeQuality,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->probeQuality(val);
            // std::cout << "probeQuality: " << val << std::endl;
        }
    );

    connect(
        ui.txt_ignoreWeakLinks,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
            trekker->ignoreWeakLinks(val);
            // std::cout << "ignoreWeakLinks: " << val << std::endl;
        }
    );

}

void RTTVIS::startRealTimeTracker()
{

    // Disable push buttons so they can't be run again in this session
    ui.InputImages->setDisabled(true);
    ui.step1_label->setDisabled(true);

    // Prepare brain mesh and peels
	brain = new Brain(fname_T1,fname_Mask,static_cast<void*>(this));
    
	// Prepare trekker
    // std::cout << "Preparing trekker... " << std::endl << std::flush ;
    ui.progressText->setText("Preparing trekker");
    ui.progressBar->setValue(40);
    std::string dir = (ui.FOD_orderOfDirections->currentText()=="Order Of Directions") ? "XYZ" : ui.FOD_orderOfDirections->currentText().toStdString();

    trekker = new Trekker(fname_FOD, dir, ui.FOD_discretization->isChecked());
    

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
	realTimePointer->Initialize(brain,trekker,static_cast<void*>(this));
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
    ui.txt_minFODamp->setValue(0.0);
    ui.txt_minFODamp->setDisabled(true);
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

    ui.tabWidget->setEnabled(true);
    ui.step3_label->setEnabled(true);

}
