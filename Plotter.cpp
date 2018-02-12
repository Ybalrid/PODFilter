#include "Plotter.hpp"

Plotter::Plotter(QWidget *parent) : QWidget(parent),
  amplifier(1)
{
	blueFill.setColor(Qt::GlobalColor::blue);
	blueFill.setStyle(Qt::BrushStyle::SolidPattern);
	bluePen.setColor(Qt::blue);
	greenFill.setColor(Qt::GlobalColor::green);
	greenFill.setStyle(Qt::BrushStyle::SolidPattern);
	greenPen.setColor(Qt::green);

	scene.setSceneRect(-100, -100, 100, 100);

	view = new QGraphicsView(&scene);
	mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(view);
	setLayout(mainLayout);

	clear();
	view->update();
}

void Plotter::setAmplifier(float amp)
{
	amplifier = amp;
}

void Plotter::clear()
{
	scene.clear();
	scene.addEllipse(0,0,25,25, bluePen, blueFill);

}

void Plotter::addPoint(qreal x, qreal y)
{
	qDebug() << "drawing " << x << "x" << y;
	scene.addEllipse(x, y, 10, 10, QPen(), greenFill);
	view->update();
}
