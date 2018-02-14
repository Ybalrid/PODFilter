#include "PODFilter.hpp"

PODFilter::PODFilter(QWidget *parent)
	: QWidget(parent)
{
	playing = false;
	setMinimumSize(1024,768);
	setWindowTitle("POD Sample analyser");

	mainLayout = new QVBoxLayout(this);
	loadCSVButton = new QPushButton("Load CSV File from POD...");
	mainLayout->addWidget(loadCSVButton);
	mainLayout->addWidget(bar = new TransportBar);
	mainLayout->addWidget(plotter = new Plotter);
	setLayout(mainLayout);

	position = 0;

	QObject::connect(loadCSVButton, &QPushButton::clicked, this, [&]
	{
		QString path = QFileDialog::getOpenFileName(this, "Open POD CSV", "", "Pod CSV (*.csv *.CSV)");
		CSVLoader loader(path.toStdString());
		data = loader.getData();

		qDebug() << "loaded " << data.size() << " samples";
		bar->setMax(data.size());
		position = 0;
	});

	QObject::connect(bar, &TransportBar::play, this, &PODFilter::play);

	QObject::connect(bar, &TransportBar::pause, this, [&]{
		playing = false;
	});


	QObject::connect(bar, &TransportBar::setTo, this, [&](const size_t& v)
	{
		position = v;
		if(!playing && position < data.size())
		{
			plotter->clear();
			plotter->addPoint(data[position].X, data[position].Y);
		}
	});

	QObject::connect(bar, &TransportBar::rewind, this, [&]{
		bar->setBarPos(0);
	});

	QObject::connect(bar, &TransportBar::forward, this, [&]{
		bar->setBarPos(data.size() - 1);
	});

	plotter->setAmplifier(5);

	QObject::connect(&t, &QTimer::timeout, this, &PODFilter::plotCurrent);

	QObject::connect(bar, &TransportBar::filtred, plotter, &Plotter::setFiltred);
}

void PODFilter::play()
{
	playing = true;
	if(position++ < data.size())
	{	CSVLoader::sample s = data[position], last = data[position -1];
		auto sampleTime = s.timecodeNanosec - last.timecodeNanosec;
		t.setInterval(sampleTime / 1000000);
		t.setSingleShot(true);
		t.start();
	}
}

void PODFilter::plotCurrent()
{
	if(position++ < data.size())
	{
		CSVLoader::sample s = data[position];
		plotter->clear();
		plotter->addPoint(s.X, s.Y);
		bar->setBarPos(position);
		if(playing) play();
	}
}

PODFilter::~PODFilter()
{

}
