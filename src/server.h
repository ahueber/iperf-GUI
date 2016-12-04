#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include "iperfinterface.h"

class TrafficLight;
class QPushButton;
class QTextEdit;
class QComboBox;
class QLabel;

class Server : public QWidget
{
    Q_OBJECT

private:
    IperfInterface *iperfInterface;
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
    QTextEdit *log;
    QComboBox *networkInterface;
    QLabel *networkInterfaceAddress;
    QMap<QString, QString> availableNetworkInterfaces;

public:
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();
    void onNetworkInterfaceDropdownChanged(const int &);

    // iperf interface slots
    void onSetTrafficLightRed();
    void onSetTrafficLightYellow();
    void onSetTrafficLightGreen();
};

#endif // SERVER_H
