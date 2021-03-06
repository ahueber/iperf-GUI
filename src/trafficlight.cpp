#include "trafficlight.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

TrafficLight::TrafficLight(QWidget *parent) : QWidget(parent) {
  layout = new QHBoxLayout();

  label = new QLabel();
  label->setScaledContents(false);
  label->setAlignment(Qt::AlignLeft);

  // QPixmap pic(":/trafficLight/images/tl_yellow.png");
}

void TrafficLight::setColor(TrafficLight::color c) {
  QPixmap pic;
  switch (c) {
  case green:
    pic.load(":/trafficLight/resources/images/tl_green.png");
    break;
  case red:
    pic.load(":/trafficLight/resources/images/tl_red.png");
    break;
  case yellow:
    pic.load(":/trafficLight/resources/images/tl_yellow.png");
    break;
  }

  label->setPixmap(pic.scaled(150, 300, Qt::KeepAspectRatio));

  layout->addWidget(label);
  this->setLayout(layout);
}
