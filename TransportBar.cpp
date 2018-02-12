#include "TransportBar.hpp"

TransportBar::TransportBar(QWidget *parent) : QWidget(parent),
	current(0),
	max(0)
{
	mainLayout = new QVBoxLayout(this);
	buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(brewind = new QPushButton("Rewind"));
	buttonLayout->addWidget(bplay = new QPushButton("Play"));
	buttonLayout->addWidget(bpause = new QPushButton("pause"));
	buttonLayout->addWidget(bforward = new QPushButton("Forward"));
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(position = new QSlider(Qt::Orientation::Horizontal));
	mainLayout->setAlignment(position, Qt::AlignTop);
	setLayout(mainLayout);

	QObject::connect(brewind, &QPushButton::clicked, this, [&]{emit rewind();});
	QObject::connect(bplay, &QPushButton::clicked, this, [&]{emit play();});
	QObject::connect(bpause, &QPushButton::clicked, this, [&]{emit pause();});
	QObject::connect(bforward, &QPushButton::clicked, this, [&]{emit forward();});
	QObject::connect(position, &QSlider::sliderMoved, this, [&](const size_t& value){
		qDebug() << value;
		float fvalue(value/100.f);
		size_t to(fvalue*max);
		qDebug() << to;
	});
}


void TransportBar::setMax(size_t m)
{
	max = m;
}

void TransportBar::setBarPos(size_t pos)
{
	float fpos(pos), fmax(max);
	float fvalue ((fpos/fmax) * 100.f);
	int value(fvalue);
	position->setValue(value);
}
