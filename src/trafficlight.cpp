#include "trafficlight.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QDebug>


TrafficLight::TrafficLight(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    //setMinimumSize(50, 100);

    QLabel *label = new QLabel();
    label->setScaledContents(false);
    label->setAlignment(Qt::AlignLeft);

    QPixmap pic(":/trafficLight/images/tl_yellow.png");

    label->setPixmap(pic.scaled(150, 300, Qt::KeepAspectRatio));

    layout->addWidget(label);
    this->setLayout(layout);

}

