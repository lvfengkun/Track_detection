#include "MainWindow.h"
#include <QFile>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QtWidgets>
#include "mainwindow.h"
#include <QString>
#include <vector>
#include <iostream>
#include <string>
#include"pin.h"
#include<qwidget.h>
#include<qpainter.h>
using namespace std;
extern int cropTrack(string cropPath, QTextEdit *textEdit);
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Main Window"));
	openAction = new QAction(QIcon("D:/opencv_data/QtGuiApplication2/QtGuiApplication2/NCU.qrc"), tr("&Open..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

	saveAction = new QAction(QIcon("D:/opencv_data/QtGuiApplication2/QtGuiApplication2/NCU.qrc"), tr("&Save..."), this);
	saveAction->setShortcuts(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save a new file"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));



	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);
	file->addAction(saveAction);

	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);

	textEdit = new QTextEdit(this);
	setCentralWidget(textEdit);
}


void MainWindow::openFile()
{
	string q2s,str;
	QString path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
	q2s = path.toStdString();
	
	cropTrack(q2s, textEdit);
	str = "cpp - home.txt";
	QString qstr;
	qstr = QString::fromStdString(str);
	QFile file(qstr);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Can't open the file!" << endl;
	}
	QTextStream in(&file);
	textEdit->setText(in.readAll());
	file.close();

}

void MainWindow::saveFile()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		out << textEdit->toPlainText();
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
	}
}
