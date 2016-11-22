#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include "iperfinterface.h"

class TrafficLight;
class QPushButton;
class QTextEdit;

class Server : public QWidget
{
    Q_OBJECT

private:
    IperfInterface *iperfInterface;
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
    QTextEdit *log;

public:
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();

    // iperf interface slots
    void onSetTrafficLightRed();
    void onSetTrafficLightYellow();
    void onSetTrafficLightGreen();
};

#endif // SERVER_H
