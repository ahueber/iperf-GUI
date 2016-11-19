#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDebug>

class ClientInterface : public QObject {
    Q_OBJECT
private:
    QString iperfPathAndFilename;
    QProcess *iperfProcess;
    QString commandLineArguments;

public:
    explicit ClientInterface(QObject *parent = 0);
    ~ClientInterface();
    void setCommandLineArguments(QString commandLineArguments);
    QStringList parseCommandLineArguments();
    bool run();
    bool stop();

signals:


public slots:
    void processReadyReadStandardOutput();
    void processReadyReadStandardError();
};

#endif // CLIENTINTERFACE_H
