#ifndef RTTVIS_GUI_H_
#define RTTVIS_GUI_H_

#include "ui_rttvis_gui.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include "trekker_interface.h"
#include "brainmesh_handler.h"

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


    // Input image file names
    std::string fname_T1;
    std::string fname_Mask;
    std::string fname_FOD;
    std::string fname_ACT;

    void startRealTimeTracker();


private:
   
   Ui::RTTVIS_GUI ui;

   Brain*   brain;
   Trekker* trekker;

   
};

#endif
