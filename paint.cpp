#include<qwidget.h>
#include<qpainter.h>

#include<QPixmap>
//!!! Qt4/Qt5
//#include<qwidget.h>
#include "pin.h"
//int a[2],b[2];
Tin::Tin(QMainWindow *parent)
	: QMainWindow(parent)
{
	/*QMouseEvent *event;
	if (event->button() == Qt::LeftButton)
	{
		m_isMousePress = true;
		m_beginPoint = event->pos();
	}*/
}

Tin::~Tin()
{

}
//鼠标按下事件：获取起始点
void Tin::mousePressEvent(QMouseEvent *event)
{
	
	/*a[0]= event->pos().x();
	a[1] = event->pos().y();*/
	if (event->button() == Qt::LeftButton)
	{
		m_isMousePress = true;
		m_beginPoint = event->pos();
	}

	return QWidget::mousePressEvent(event);
}
void Tin::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isMousePress)
	{
		m_endPoint = event->pos();
		update();
	}
	return QWidget::mouseMoveEvent(event);
}
//鼠标释放事件：获取终点
void Tin::mouseReleaseEvent(QMouseEvent *event)
{
	/*b[0] = event->pos().x();
	b[1] = event->pos().y();*/
	m_endPoint = event->pos();
	m_isMousePress = false;
	return QWidget::mouseReleaseEvent(event);
}
//窗口绘制事件：确定绘制的窗口，添加绘制的颜色，绘制直线的起点和终点。
void Tin::paintEvent(QPaintEvent *event)
{
	QPixmap pixmap("E:\\songhui\\detectArcs\\trackImgs\\images\\0km_2m_10.bmp");
	//根据鼠标起点到终点绘制直线
	QPainter painter(this);
	painter.drawPixmap(rect(), pixmap);
	painter.setPen(Qt::red);
	painter.drawRect(m_beginPoint.x(), m_beginPoint.y(), m_endPoint.x(), m_endPoint.y());
    update();
}
