#ifndef RTTVIS_APP_H_
#define RTTVIS_APP_H_

#include "ui_rttvis_app.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

class RTTVIS_APP : public QMainWindow
{
    Q_OBJECT

public:
    RTTVIS_APP(QMainWindow *parent = 0);
    ~RTTVIS_APP();
    void addWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow> window);
    vtkSmartPointer<vtkRenderWindowInteractor> getWindowInteractor() {return ui.qvtkOpenGLStereoWidget->interactor();};

private:
   
   Ui::RTTVIS_APP ui;
   
};

#endif
