#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QDebug>
#include <QPen>
#include <QBrush>

#include <algorithm>
#include <tuple>

class Plotter : public QWidget
{
		Q_OBJECT
	public:
		explicit Plotter(QWidget *parent = nullptr);
		void setAmplifier(float amp);
		void setFilterSize(int dim);
		std::tuple<qreal, qreal>  filter(qreal x, qreal y);

	signals:

	public slots:
		void clear();
		void addPoint(qreal x, qreal y);
		void setFiltred(bool);

	private:
		bool showFiltred;
		QHBoxLayout* mainLayout;
		QGraphicsView* view;
		QGraphicsScene scene;
		QBrush blueFill;
		QPen bluePen;
		QBrush greenFill;
		QPen greenPen;
		QBrush redFill;
		float amplifier;
#define MAX_DIM 20
		int xbuf[MAX_DIM], ybuf[MAX_DIM];
		int dim;
};

#endif // PLOTTER_HPP
