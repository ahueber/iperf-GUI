#ifndef IPERFINTERFACE_H
#define IPERFINTERFACE_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QRegExp>
#include <QDebug>

#define IPERF_PATH_AND_FILENAME "/usr/bin/iperf"
#define MSG_SERVER_LISTENING "Server listening on UDP port [0-9]+"
#define MSG_CONNECTION_ESTABLISHED "[a-zA-Z0-9]+ (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+ connected with (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+"


class IperfInterface : public QProcess {
    Q_OBJECT

private:
    QString initialArguments;

    QStringList parseArguments(QString arguments);

public:
    bool serverIsListening = false;

    IperfInterface(QString initialArguments = QString());
    ~IperfInterface();

    void setInitialArguments(QString initialArguments);
    QString getInitialArguments();

    void run();

signals:
    void logOutput(const QString &);

public slots:
    void processReadyReadStandardOutput();

};

#endif // IPERFINTERFACE_H
