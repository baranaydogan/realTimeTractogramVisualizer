#include "rttvis_gui.h"
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <qaction.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <QTimer>
#include <qdialog.h>


RTTVIS::RTTVIS(QMainWindow *parent) : QMainWindow(parent) {

	ui.setupUi(this);
    
    clipboard = QApplication::clipboard();


    // Menu
    connect(
        ui.actionAbout, 
        &QAction::triggered,
        [&](){
            dialogAbout.exec();
        }
    );

    // Initialization
    connect(
        ui.push_T1, 
        &QPushButton::clicked,
        [&](){
            QString tmp = QFileDialog::getOpenFileName(this,tr("Load T1"), "", tr("Nifti image (*.nii *.nii.gz)"));
            if (tmp!="") {
                ui.fname_T1_line->setText(tmp);
                fname_T1 = tmp.toStdString();
            }
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
            if (tmp!="") {
                ui.fname_Mask_line->setText(tmp);
                fname_Mask = tmp.toStdString();
            }
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
            if (tmp!="") {
                ui.fname_FOD_line->setText(tmp);
                fname_FOD = tmp.toStdString();
            }
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
            if (tmp!="") {
                ui.fname_ACT_line->setText(tmp);
                fname_ACT = tmp.toStdString();
            }
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

    // Visualization

    connect(
        ui.txt_peelNo,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            looper->peelNo = ui.txt_peelNo->value();
			looper->updatePeel();
        }
    );

    
    connect(
        ui.txt_maxStreamlineCount,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
           looper->setMaxShown(val);
        }
    );

    connect(
        ui.txt_batchCount,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            if (val>ui.txt_maxStreamlineCount->value())
                looper->setBatchSize(ui.txt_maxStreamlineCount->value());
            else
                looper->setBatchSize(val);
        }
    );

    
    connect(
        ui.txt_tubeRadius,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
           looper->setTubeRadius(val);
        }
    );

    connect(
        ui.txt_addOpacity,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
           looper->setAddedOpacity(val);
        }
    );

    connect(
        ui.txt_seed_radius,
        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [&](double val){
           looper->setSeedRadius(val);
        }
    );
    

    // Tracking

    connect(
        ui.txt_seed_maxTrials,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [&](int val){
            trekker->seed_maxTrials(val);
        }
    );

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

    // Center view
    connect(ui.push_centerView, 
        &QPushButton::clicked,
        [&](){

            looper->interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
			looper->interactor->InvokeEvent(vtkCommand::LeftButtonPressEvent);
			looper->interactor->InvokeEvent(vtkCommand::LeftButtonReleaseEvent);

            QString prevInfo = ui.txt_info->text(); 
            ui.txt_info->setText("View centered");
            QTimer::singleShot(3000, this, [this,prevInfo](){ ui.txt_info->setText(prevInfo); });
        }
    );

    // Copy to clipboard
    connect(ui.push_copyToClipboard, 
        &QPushButton::clicked,
        [&](){

            clipboard->clear();
            clipboard->setText(ui.txt_coordinates->text());

            QString prevInfo = ui.txt_info->text();          
            ui.txt_info->setText("Coordinates copied");
            QTimer::singleShot(3000, this, [this,prevInfo](){ ui.txt_info->setText(prevInfo); });
        }
    );

}

void RTTVIS::startRealTimeTracker()
{

    // Disable push buttons so they can't be run again in this session
    ui.InputImages->setDisabled(true);
    ui.StartTracker->setDisabled(true);
    ui.push_start->setDisabled(true);
    

    // Prepare brain mesh and peels
	brain = new Brain(fname_T1,fname_Mask,static_cast<void*>(this));
    
	// Prepare trekker
    // std::cout << "Preparing trekker... " << std::endl << std::flush ;
    ui.progressText->setText("Preparing Trekker (this might take some time)");
    ui.progressBar->setValue(40);

    std::string dir = (ui.FOD_orderOfDirections->currentText()=="Order Of Directions") ? "XYZ" : ui.FOD_orderOfDirections->currentText().toStdString();
    trekker = new Trekker(fname_FOD, dir, ui.FOD_discretization->isChecked());
    ui.progressBar->setValue(100);
    ui.progressText->setText("Ready");
    ui.progressBar->setDisabled(true);
    

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

    // trekker->printParameters();
	
    std::cout << std::endl << std::flush ;    
    
    // Prepare user interface
	looper = vtkSmartPointer<vtkTimerCallback>::New();
	looper->Initialize(brain,trekker,static_cast<void*>(this));

    // Update parameters in GUI

    // Visualization
    ui.txt_peelNo->setMaximum(brain->numberOfPeels);
    ui.txt_peelNo->setValue(looper->peelNo);
    ui.txt_seed_radius->setValue(looper->seedRadius);
    ui.txt_maxStreamlineCount->setValue(looper->maxAllowedToShow);
    ui.txt_batchCount->setValue(looper->batchSize);
    ui.txt_tubeRadius->setValue(looper->tubeRadius);
    ui.txt_addOpacity->setValue(looper->addedOpacity);
    
    // Tracking
    ui.txt_numberOfThreads->setValue(trekker->getNumberOfThreads());
    ui.txt_seed_maxTrials->setValue(trekker->getSeed_maxTrials());
    ui.txt_minLength->setValue(trekker->getMinLength());
    ui.txt_maxLength->setValue(trekker->getMaxLength());
    ui.txt_stepSize->setValue(trekker->getStepSize());
    ui.txt_minRadiusOfCurvature->setValue(trekker->getMinRadiusOfCurvature());
    ui.txt_minFODamp->setValue(0);
    ui.txt_minFODamp->setDisabled(true);
    ui.txt_dataSupportExponent->setValue(trekker->getDataSupportExponent());
    ui.txt_writeInterval->setValue(trekker->getWriteInterval());
    ui.txt_atMaxLength->setCurrentText(QString::fromStdString(trekker->getAtMaxLength()));
    ui.txt_directionality->setCurrentText(QString::fromStdString(trekker->getDirectionality()));

    // Advanced
    ui.txt_maxEstInterval->setValue(trekker->getMaxEstInterval());
    ui.txt_initMaxEstTrials->setValue(trekker->getInitMaxEstTrials());
    ui.txt_propMaxEstTrials->setValue(trekker->getPropMaxEstTrials());
    ui.txt_maxSamplingPerStep->setValue(trekker->getMaxSamplingPerStep());
    ui.check_useBestAtInit->setChecked(trekker->getUseBestAtInit());

    ui.txt_probeLength->setValue(trekker->getProbeLength());
    ui.txt_probeRadius->setValue(trekker->getProbeRadius());
    ui.txt_probeCount->setValue(trekker->getProbeCount());
    ui.txt_probeQuality->setValue(trekker->getProbeQuality());
    ui.txt_ignoreWeakLinks->setValue(trekker->getIgnoreWeakLinks());



    // Enable widget
    ui.tabWidget->setEnabled(true);
    ui.scrollArea_1->setEnabled(true);
    ui.scrollArea_2->setEnabled(true);
    ui.scrollArea_3->setEnabled(true);
    ui.txt_seed_radius->setEnabled(true);
    ui.txt_seed_radius_label->setEnabled(true);
    ui.interact_label->setEnabled(true);
    ui.push_centerView->setEnabled(true);
    ui.push_copyToClipboard->setEnabled(true);

    ui.txt_numberOfThreads->setDisabled(true);
    ui.txt_numberOfThreads_label->setDisabled(true);

    ui.txt_minFODamp->setDisabled(true);
    ui.txt_minFODamp_label->setDisabled(true);


}
