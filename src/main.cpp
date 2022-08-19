#include "aux.h"
#include <QFontDatabase>

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	// Load the embedded font.
	QString fontPath = ":/DejaVuSans.ttf";
	QFontDatabase::addApplicationFont(fontPath);
	QFont font("DejaVuSans");
	if (font.pointSize() != -1) 
		font.setPointSize(font.pointSize()*0.8);
	else
		font.setPixelSize(font.pixelSize()*0.8);
	app.setFont(font);
	

	auto renderer 	= vtkSmartPointer<vtkRenderer>::New();
	RTTVIS* dialog  = startRenderer(renderer);
	app.exec();

	delete dialog;

	return EXIT_SUCCESS;
}
