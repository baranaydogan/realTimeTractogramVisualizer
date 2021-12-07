#include "rttvis_app.h"

RTTVIS_APP::RTTVIS_APP(QMainWindow *parent) : QMainWindow(parent) {
	ui.setupUi(this);
}

RTTVIS_APP::~RTTVIS_APP() { }

void RTTVIS_APP::addWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow> window) {
	ui.qvtkOpenGLStereoWidget->setRenderWindow(window);
}
