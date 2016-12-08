#ifndef IPERFINTERFACE_H
#define IPERFINTERFACE_H

#include <QObject>
#include <QMap>
#include <QProcess>
#include <QtNetwork>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QRegExp>
#include <QFile>
#include <QFileSystemWatcher>
#include <QTextStream>
#include <QDebug>

#define IPERF_PATH_AND_FILENAME "/usr/bin/iperf3"

#define MSG_SERVER_LISTENING "Server listening on UDP port [0-9]+"
//#define MSG_CONNECTION_ESTABLISHED "[a-zA-Z0-9]+ (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+ connected with (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+"
#define MSG_CONNECTION_ESTABLISHED "Accepted connection from"
#define MSG_CONNECTION_CLOSED "receiver"
#define MSG_CLIENT_CONNECTION_REFUSED "read failed: Connection refused"


class IperfInterface : public QProcess {
    Q_OBJECT

private:
    QString initialArguments;
    QString logPathAndFilename;

    bool serverIsListening = false;
    bool clientConnected = false;

    QFileSystemWatcher *logFileWatcher;
    QFile *logFile;

    QStringList parseCombinedArgString(const QString &program);
    QString getLastLine(const QString &text);
    void parseLogOutput(const QString &logOutput);
    void clearLogFile();

public:
    IperfInterface(QString initialArguments = QString(), QString logPathAndFilename = QString("/tmp/iperf3.log"));
    ~IperfInterface();

    void setInitialArguments(QString initialArguments);
    QString getInitialArguments();

    //void setLogPathAndFilename(QString logPathAndFilename);
    QString getLogPathAndFilename();

    void setServerIsListening(bool serverIsListening);
    bool getIsServerListening();

    QMap<QString, QString> getNetworkInterfaces();

    void run();

signals:
    void logOutput(const QString &);
    void serverStartedListening();
    void connectionEstablished();
    void connectionClosed();

public slots:
    void processReadyReadStandardOutput();
    void processFileChanged(const QString &);

};

#endif // IPERFINTERFACE_H
