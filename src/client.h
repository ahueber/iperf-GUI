/**
 * @file client.h
 * @brief A brief description about this header file.
 *
 * A long description about this header file.
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
 * @brief The Client class
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
     * @brief Client
     * @param parent
     */
    explicit Client(QWidget *parent = 0);

signals:

public slots:
    /**
     * @brief A brief description about this slot.
     */
    void onExitButtonClicked();   
    /**
     * @brief A brief description about this slot.
     */
    void onStartButtonClicked();
    /**
     * @brief A brief description about this slot.
     */
    void onKeyboardClicked();
    /**
     * @brief A brief description about this slot.
     */
    void onRuntimeChanged(int);
    /**
     * @brief A brief description about this slot.
     */
    void onBandwidthChanged(int);
    /**
     * @brief setIP
     * @param s
     */
    void setIP(QString s);
    /**
     * @brief getIP
     * @return
     */
    QString getIP();
};

#endif // CLIENT_H
