#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

class TrafficLight;
class QPushButton;
class QComboBox;
class QSlider;
class QLineEdit;

class Client : public QWidget
{
    Q_OBJECT
private:
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
    QSlider *sliderRuntime;
    QSlider *sliderBandwidth;
    QComboBox *fieldModus;
    QLineEdit *fieldRuntime;
    QLineEdit *fieldBandwidth;

public:
    explicit Client(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();
    void onRuntimeChanged(int);
    void onBandwidthChanged(int);
};

#endif // CLIENT_H
