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
template <typename T, typename S> T lerp(T a, T b, S w)
{
	return  a + w * (b - a);
}
std::tuple<qreal, qreal> Plotter::filter(qreal x, qreal y)
{
	static int fx, fy;

	std::rotate(std::rbegin(xbuf), std::rbegin(xbuf)+1, std::rend(xbuf));
	std::rotate(std::rbegin(ybuf), std::rbegin(ybuf)+1, std::rend(ybuf));
	xbuf[0] = x;
	ybuf[0] = y;

	const float scale = 0.9f;

	if(std::abs(xbuf[0] - xbuf[1]) > 5 && std::abs(xbuf[0]) > 10)
	{
		qDebug() << "Weird data right here! o.O";
		xbuf[0] = lerp(xbuf[0], xbuf[2], scale);

	}
	if(std::abs(ybuf[0] - ybuf[1]) > 5 && std::abs(ybuf[0]) > 10)
	{
		qDebug() << "Weird data right here! o.O";
		ybuf[0] = lerp(ybuf[0], ybuf[2], scale);
	}

	fx = fy = 0;
	for(int i = 0; i < dim; ++i)
	{
		fx += xbuf[i];
		fy += ybuf[i];
	}

	fx /= dim;
	fy /= dim;

	return std::tie(fx, fy);
}

void Plotter::addPoint(qreal x, qreal y)
{
	qDebug() << "drawing " << x << "x" << y;
	auto filtered = filter(x, y);
	if(showFiltred)
		scene.addEllipse(amplifier * std::get<0>(filtered), amplifier * std::get<1>(filtered), 10, 10, QPen(), redFill);
	else
		scene.addEllipse(amplifier * x, amplifier * y, 10, 10, QPen(), greenFill);

	view->update();
}

void Plotter::setFiltred(bool s)
{
	showFiltred = s;
}

void Plotter::setFilterSize(int d)
{
	if(d > 1 && d < MAX_DIM) dim = d;
}
