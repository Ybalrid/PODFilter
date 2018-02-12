#ifndef PODFILTER_HPP
#define PODFILTER_HPP

#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include "TransportBar.hpp"
#include "Plotter.hpp"
#include "CSVLoader.hpp"

class PODFilter : public QWidget
{
		Q_OBJECT

	public:
		PODFilter(QWidget *parent = 0);
		~PODFilter();
	public slots:
		void play();
		void plotCurrent();
	private:
		QVBoxLayout* mainLayout;
		QPushButton* loadCSVButton;
		TransportBar* bar;
		Plotter* plotter;

		CSVLoader::sampleVect data;

		size_t position;
		QTimer t;

		bool playing;


};

#endif // PODFILTER_HPP
