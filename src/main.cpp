#include "aux.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	auto renderer 	= vtkSmartPointer<vtkRenderer>::New();
	RTTVIS* dialog  = startRenderer(renderer);
	app.exec();

	delete dialog;

	return EXIT_SUCCESS;
}
