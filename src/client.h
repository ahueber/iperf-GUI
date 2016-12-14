/**
 * @file client.h
 * @brief Das Widget für den Clientbetrieb.
 *
 * Diese Klasse repräsentiert das Widget für den Clientbetrieb der Applikation.
 * Dieses Widget wird vom Willkommen-Widget geöffnet.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "iperfinterface.h"

class TrafficLight;
class QPushButton;
class QRadioButton;
class QSlider;
class QLineEdit;

#define IPERF_CLIENT_DUPLEX_MODE_ARGS "-c {{IP_ADDRESS}} -u -P 1 -i 1 -p 5001 -f m -b {{BANDWIDTH}} -t {{TIME}} -d -L 5001 -T 1"
#define IPERF_CLIENT_SIMPLEX_MODE_ARGS "-c {{IP_ADDRESS}} -u -P 1 -i 1 -p 5001 -f m -b {{BANDWIDTH}} -t {{TIME}} -T 1"

/**
 * @brief Die Client-Klasse
 */
class Client : public QWidget
{
    Q_OBJECT
private:
    IperfInterface *iperfInterface;
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
    QSlider *sliderRuntime;
    QSlider *sliderBandwidth;
    QRadioButton *simplex;
    QRadioButton *duplex;
    QLineEdit *fieldRuntime;
    QLineEdit *fieldBandwidth;
    QLineEdit *fieldIP;

    /**
     * @brief Erstellt einen String der dem Iperf CLI Tool übergeben werden kann
     * @param ipAddress Die IP-Adresse zu welchem der Client sich verbinden soll
     * @param bandwidth Die Bandbreite für die Übertragung im Format #[KMG]
     * @param time Die Zeit in Sekunden bis der Client sich disconnected
     * @param mode Modus für die Verbindung zum Server (Simplex = 0 [default], Duplex = 1)
     * @return iperf3 kompatibler String aus Argumenten
     */
    QString createIperfArgumentString(QString ipAddress, QString bandwidth, int time, int mode = 0);

public:
    /**
     * @brief Client Konstruktor
     * @param parent
     */
    explicit Client(QWidget *parent = 0);

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
     * @brief Beim Klicken des Keyboard-Button aufgerufene Handler-Methode.
     */
    void onKeyboardClicked();
    /**
     * @brief Beim Bewegen oder Anklicken des Slider "Laufzeit" aufgerufene Handler-Methode.
     */
    void onRuntimeChanged(int);
    /**
     * @brief Beim Bewegen oder Anklicken des Slider "Bandbreite" aufgerufene Handler-Methode.
     */
    void onBandwidthChanged(int);
    /**
     * @brief Setzt die IP-Adresse.
     * @param s Die IP-Adresse als String im Format 192.168.0.40
     */
    void setIP(QString s);
    /**
     * @brief Gibt die IP-Adresse zurück.
     * @return Die IP-Adresse als String im Format 192.168.0.40
     */
    QString getIP();
};

#endif // CLIENT_H
