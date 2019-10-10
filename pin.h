#pragma once
//!!! Qt4/Qt5
#ifndef TIN_H
#define TIN_H

#include "QtWidgets/QMainWindow"
//#include "ui_tin.h"
#include<ui_ImageProcessing.h>
#include "QPaintEvent"
#include "QList"
#include "QMouseEvent"
#include<qlabel.h>
class Tin : public QMainWindow
{
	Q_OBJECT

public:
	Tin(QMainWindow *parent = 0);
	~Tin();
	//定义鼠标状态（按下，移动，释放）三个事件，定义绘制事件
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
private:
	bool m_isMousePress;
	QPoint m_beginPoint, m_endPoint;
};
#endif // TIN_H
