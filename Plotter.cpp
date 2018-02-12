#include "Plotter.hpp"

Plotter::Plotter(QWidget *parent) : QWidget(parent),
  amplifier(1),
  dim(5)
{
	blueFill.setColor(Qt::GlobalColor::blue);
	blueFill.setStyle(Qt::BrushStyle::SolidPattern);
	bluePen.setColor(Qt::blue);
	greenFill.setColor(Qt::GlobalColor::green);
	greenFill.setStyle(Qt::BrushStyle::SolidPattern);
	greenPen.setColor(Qt::green);
	redFill.setColor(Qt::GlobalColor::red);
	redFill.setStyle(Qt::BrushStyle::SolidPattern);

	scene.setSceneRect(-100, -100, 100, 100);

	view = new QGraphicsView(&scene);
	mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(view);
	setLayout(mainLayout);

	clear();
	view->update();
	for(size_t i{0}; i < MAX_DIM; ++i)
	{
		xbuf[i] = 0; ybuf[i] = 0;
	}
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
	std::rotate(std::rbegin(xbuf), std::rbegin(xbuf)+1, std::rend(xbuf));
	std::rotate(std::rbegin(ybuf), std::rbegin(ybuf)+1, std::rend(ybuf));
	xbuf[0] = x;
	ybuf[0] = y;
	scene.addEllipse(amplifier * x, amplifier * y, 10, 10, QPen(), greenFill);

	int fx = 0, fy = 0;;
	for(int i = 0; i < dim; ++i)
	{
		fx += xbuf[i];
		fy += ybuf[i];
	}

	fx /= dim;
	fy /= dim;

	scene.addEllipse(amplifier * fx, amplifier * fy, 5, 5, QPen(), redFill);

	view->update();
}

void Plotter::setFilterSize(int d)
{
	if(d > 1 && d < MAX_DIM) dim = d;
}
