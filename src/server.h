#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTextCursor>
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
    QTextCursor c;

    void setIsRunning();
    void setIsNotRunning();
    void setIsRunningAndConnected();

public:
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();
    void onNetworkInterfaceDropdownChanged(const int &);
    void setCursor();

    // iperf interface slots
    void onProcessStateChanged(const QProcess::ProcessState &newState);
    void onConnectionEstablished();
    void onConnectionClosed();
};

#endif // SERVER_H
