#ifndef RTTVIS_GUI_H_
#define RTTVIS_GUI_H_

#include "ui_rttvis_gui.h"
#include "ui_gui_about.h"

#include <qdialog.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include "trekker_interface.h"
#include "brainmesh_handler.h"

#include <QClipboard>
#include <QImage>
#include <QMovie>
#include <QDir>

class About : public QDialog
{
    Q_OBJECT
public:

    About(QDialog *parent = 0) {

        Q_INIT_RESOURCE(resources);

        ui.setupUi(this);

        anim = new QMovie(this);
        anim->setFileName(":/anim.gif");
        ui.gifFrame->setMovie(anim);
        ui.gifFrame->setScaledContents(true);
        anim->start();
    };

    Ui::DialogAbout ui;
    QMovie* anim;
};

class RTTVIS : public QMainWindow
{
    Q_OBJECT

public:

    RTTVIS(QMainWindow *parent = 0);

    ~RTTVIS() {
        delete brain;
        delete trekker;
    };

    void addWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow> window) {
        ui.qvtkOpenGLStereoWidget->setRenderWindow(window);
    };

    vtkSmartPointer<vtkRenderWindowInteractor> getWindowInteractor() {
        return ui.qvtkOpenGLStereoWidget->interactor();
    };

    QClipboard *clipboard;

    // Input image file names
    std::string fname_T1;
    std::string fname_Mask;
    std::string fname_FOD;
    std::string fname_ACT;

    // Interactor
    vtkSmartPointer<vtkTimerCallback> looper;
    void startRealTimeTracker();

    Brain*   brain;
    Trekker* trekker;

    Ui::RTTVIS_GUI   ui;
    About            dialogAbout;

};

#endif
