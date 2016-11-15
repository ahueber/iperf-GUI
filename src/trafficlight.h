#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class TrafficLight : public QWidget
{
    Q_OBJECT
private:
    QLabel *label;
    QHBoxLayout *layout;
public:
    enum color{green, red, yellow};
    explicit TrafficLight(QWidget *parent = 0);
    void setColor(color c);

signals:

public slots:
};

#endif // TRAFFICLIGHT_H
