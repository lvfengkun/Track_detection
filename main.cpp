#include <QApplication>
#include <QCoreApplication>
#include "MainWindow.h"
#include<pin.h>
#include <QObject>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//Tin t;
	//t = new Tin();
	//t->setWindowTitle("test_1");
	
	MainWindow win;
    //QObject::connect(&win, SIGNAL(send_signal()), &t, SLOT(paintEvent(QPaintEvent *event)));
	win.show();

	return app.exec();
}
