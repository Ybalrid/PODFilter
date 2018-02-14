#include "TransportBar.hpp"

TransportBar::TransportBar(QWidget *parent) : QWidget(parent),
	current(0),
	max(0)
{
	QLabel* l;
	mainLayout = new QVBoxLayout(this);
	buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(brewind = new QPushButton("Rewind"));
	buttonLayout->addWidget(bplay = new QPushButton("Play"));
	buttonLayout->addWidget(bpause = new QPushButton("pause"));
	buttonLayout->addWidget(bforward = new QPushButton("Forward"));
	buttonLayout->addWidget(l = new QLabel("showFiltred"));
	buttonLayout->addWidget(bfiltred = new QCheckBox);
	buttonLayout->setAlignment(bfiltred, Qt::AlignRight);
	buttonLayout->setAlignment(l, Qt::AlignLeft);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(position = new QSlider(Qt::Orientation::Horizontal));
	mainLayout->setAlignment(position, Qt::AlignTop);
	setLayout(mainLayout);

	QObject::connect(brewind, &QPushButton::clicked, this, [&]{emit rewind();});
	QObject::connect(bplay, &QPushButton::clicked, this, [&]{emit play();});
	QObject::connect(bpause, &QPushButton::clicked, this, [&]{emit pause();});
	QObject::connect(bforward, &QPushButton::clicked, this, [&]{emit forward();});
	QObject::connect(position, &QSlider::valueChanged, this, [&](const size_t& value){
		emit setTo(value);
	});
	QObject::connect(bfiltred, &QCheckBox::toggled, this, [&](bool state){
		emit filtred(state);
	});

//	QObject::connect(this, &TransportBar::setTo, this, [&](const size_t& v){
//		qDebug() << "setTo(" << v << ")";
//	});
}


void TransportBar::setMax(size_t m)
{
	max = m;
	position->setRange(0, max);
}

void TransportBar::setBarPos(size_t pos)
{
	position->setValue(pos);
}
