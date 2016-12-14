/**
 * @file server.h
 * @brief Das Widget für den Serverbetrieb.
 *
 * Diese Klasse repräsentiert das Widget für den Serverbetrieb der Applikation.
 * Dieses Widget wird vom Willkommen-Widget geöffnet.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTextCursor>
#include "iperfinterface.h"

#define IPERF_SERVER_MODE_ARGS "-s -p 5001"

class TrafficLight;
class QPushButton;
class QTextEdit;
class QComboBox;
class QLabel;

/**
 * @brief Die Server-Klasse
 */
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
    /**
     * @brief Der Server-Konstruktor
     * @param parent
     */
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    /**
     * @brief Beim Klicken des Schliessen-Button aufgerufene Handler-Methode.
     */
    void onExitButtonClicked();
    /**
     * @brief Beim Klicken des Starten-Button aufgerufene Handler-Methode.
     */
    void onStartButtonClicked();
    /**
     * @brief Beim Wechseln des Dropdown für das Netzwerk-Interface aufgerufene Handler-Methode.
     */
    void onNetworkInterfaceDropdownChanged(const int &);
    /**
     * @brief Setzt den Cursor im Feld für die Logausgabe
     */
    void setCursor();

    // iperf interface slots
    /**
     * @brief Beim Ändern des Prozessstatus des Netzwerk-Interface aufgerufene Handler-Methode.
     * @param newState
     */
    void onProcessStateChanged(const QProcess::ProcessState &newState);
    /**
     * @brief Beim Aufbauen der Netzwerk-Verbindung aufgerufene Handler-Methode.
     */
    void onConnectionEstablished();
    /**
     * @brief Beim Schliessen der Netzwerk-Verbindung aufgerufene Handler-Methode.
     */
    void onConnectionClosed();
};

#endif // SERVER_H
