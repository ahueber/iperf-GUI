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

class TrafficLight;
class QPushButton;
class QRadioButton;
class QSlider;
class QLineEdit;

/**
 * @brief Die Client-Klasse
 */
class Client : public QWidget
{
    Q_OBJECT
private:
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
