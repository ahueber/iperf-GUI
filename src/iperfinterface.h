/**
 * @file iperfinterface.h
 * @brief Die Schnittstellen-Klasse für iperf3
 *
 * Diese Klasse fungiert als Schnittstelle zwischen der GUI-Applikation und dem Kommandozeilenprogramm iperf3.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

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
#define MSG_SERVER_HAS_TERMINATED "the server has terminated"
//#define MSG_CONNECTION_ESTABLISHED "[a-zA-Z0-9]+ (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+ connected with (?:[0-9]{1,3}.){3}[0-9]{1,3} port [0-9]+"
#define MSG_CONNECTION_ESTABLISHED "Accepted connection from"
#define MSG_CONNECTION_CLOSED "Lost/Total Datagrams"
#define MSG_SOCKET_UNEXPECTEDLY_CLOSED "control socket has closed unexpectedly"
#define MSG_CLIENT_CONNECTION_REFUSED "Connection refused"
#define MSG_CLIENT_HAS_TERMINATED "iperf3: the client has terminated"
#define MSG_CLIENT_UNEXPECTEDLY_CLOSED "the client has unexpectedly closed the connection"
#define MSG_CLIENT_HAS_FINISHED "iperf Done."


/**
 * @brief Die IperfInterface-Klasse
 */
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
    /**
     * @brief Der IperfInterface-Konstruktor
     * @param initialArguments Die Argumente-Liste, welche an das Kommandozeilenprogramm übermittelt werden.
     * @param logPathAndFilename Der Pfad zur Logdatei.
     */
    IperfInterface(QString initialArguments = QString(), QString logPathAndFilename = QString("/tmp/iperf3.log"));
    ~IperfInterface();

    /**
     * @brief Setzt die Argumente-Liste
     * @param initialArguments Die Argumente-Liste als String.
     */
    void setInitialArguments(QString initialArguments);

    /**
     * @brief Gibt die Argumente-Liste als String zurück.
     * @return Die Argumente-Liste als String.
     */
    QString getInitialArguments();

    //void setLogPathAndFilename(QString logPathAndFilename);
    /**
     * @brief Gibt den Pfad zur Logdatei zurück.
     * @return Der Pfad als String.
     */
    QString getLogPathAndFilename();

    /**
     * @brief Setzt den Server auf "Listening".
     * @param serverIsListening
     */
    void setServerIsListening(bool serverIsListening);

    /**
     * @brief Gibt zurück ob der Server auf "Listening" gesetzt ist.
     * @return Den Status "Listening"
     */
    bool getIsServerListening();

    /**
     * @brief Gibt die Netzwerkschnittstellen als Map zurück.
     * @return Die Netzwerkschnittstellen
     */
    QMap<QString, QString> getNetworkInterfaces();

    /**
     * @brief Startet das Kommandozeilenprogramm iperf3.
     */
    void run();

signals:
    /**
     * @brief Signal wenn der Output geloggt wird.
     */
    void logOutput(const QString &);    
    /**
     * @brief Signal wenn Start des Servers abgeschlossen ist.
     */
    void serverStartedListening();    
    /**
     * @brief Signal wenn die Verbindung zwischen Client und Server aufgebaut ist.
     */
    void connectionEstablished();    
    /**
     * @brief Signal wenn die Verbindung zwischen Client und Server geschlossen wurde.
     */
    void connectionClosed();

public slots:
    /**
     * @brief Bei der Bereitschaft des Prozesses aufgerufene Handler-Methode.
     */
    void processReadyReadStandardOutput();
    /**
     * @brief Beim Ändern der Logdatei aufgerufene Handler-Methode.
     */
    void processFileChanged(const QString &);

};

#endif // IPERFINTERFACE_H
