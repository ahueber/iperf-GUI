#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

class TrafficLight;
class QPushButton;

class Client : public QWidget
{
    Q_OBJECT
private:
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
public:
    explicit Client(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();
};

#endif // CLIENT_H
