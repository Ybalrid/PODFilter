#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QDebug>
#include <QPen>
#include <QBrush>

class Plotter : public QWidget
{
		Q_OBJECT
	public:
		explicit Plotter(QWidget *parent = nullptr);
		void setAmplifier(float amp);

	signals:

	public slots:
		void clear();
		void addPoint(qreal x, qreal y);
	private:
		QHBoxLayout* mainLayout;
		QGraphicsView* view;
		QGraphicsScene scene;
		QBrush blueFill;
		QPen bluePen;
		QBrush greenFill;
		QPen greenPen;
		float amplifier;
};

#endif // PLOTTER_HPP
