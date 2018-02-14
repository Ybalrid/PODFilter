#ifndef TRANSPORTBAR_HPP
#define TRANSPORTBAR_HPP

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QCheckBox>

class TransportBar : public QWidget
{
		Q_OBJECT
	public:
		explicit TransportBar(QWidget *parent = nullptr);

	signals:
		void play();
		void pause();
		void rewind();
		void forward();
		void setTo(size_t);

		void filtred(bool);
	public slots:

		void setMax(size_t m);
		void setBarPos(size_t pos);

	private:
		QVBoxLayout* mainLayout;
		QHBoxLayout* buttonLayout;
		QPushButton *bplay, *bpause, *bforward, *brewind;
		size_t current, max;
		QSlider* position;
		QCheckBox* bfiltred;
};

#endif // TRANSPORTBAR_HPP
