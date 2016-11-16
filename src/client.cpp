#include "client.h"
#include "trafficlight.h"
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSlider>

Client::Client(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::yellow);

    //labels
    QFont font;
    font.setBold(true);
    font.setPointSize(20);

    QLabel *labelIP = new QLabel("IP");
    labelIP->setFont(font);
    QLabel *labelModus = new QLabel("Modus");
    labelModus->setFont(font);
    QLabel *labelRuntime = new QLabel("Laufzeit");
    labelRuntime->setFont(font);
    QLabel *labelBandwidth = new QLabel("Bandbreite");
    labelBandwidth->setFont(font);
    labelBandwidth->setFixedWidth(180);

    //data entry fields
    QLineEdit *fieldIP = new QLineEdit();
    fieldIP->setFont(font);
    fieldIP->setPlaceholderText("z.B. 192.168.1.37");

    fieldModus = new QComboBox();
    fieldModus->addItem("Duplex");
    fieldModus->addItem("Simplex");

    fieldRuntime = new QLineEdit();
    fieldRuntime->setFixedWidth(100);

    fieldBandwidth = new QLineEdit();
    fieldBandwidth->setFixedWidth(100);

    //sliders
    sliderRuntime = new QSlider(Qt::Horizontal);
    sliderRuntime->setRange(0, 100);
    sliderRuntime->setSingleStep(1);

    sliderBandwidth = new QSlider(Qt::Horizontal);
    sliderBandwidth->setRange(0, 100);
    sliderBandwidth->setSingleStep(1);

    //buttons
    QPushButton *exitButton = new QPushButton("Close");
    startButton = new QPushButton("Start");
    QPushButton *keyboard = new QPushButton("...");
    keyboard->setFixedWidth(30);

    //set position in grid
    layout->addWidget(tl, 0, 0, 4, 1, Qt::AlignCenter);
    layout->addWidget(labelIP, 0, 1);
    layout->addWidget(labelModus, 1, 1);
    layout->addWidget(labelRuntime, 2, 1);
    layout->addWidget(labelBandwidth, 3, 1);
    layout->addWidget(fieldIP, 0, 2, 1, 2);
    layout->addWidget(fieldModus, 1, 2, 1, 2);
    layout->addWidget(fieldRuntime, 2, 2);
    layout->addWidget(fieldBandwidth, 3, 2);
    layout->addWidget(sliderRuntime, 2, 3);
    layout->addWidget(sliderBandwidth, 3, 3);
    layout->addWidget(keyboard, 0, 4);
    layout->addWidget(startButton, 4, 1, 1, 2);
    layout->addWidget(exitButton, 4, 3, 1, 2);

    //connectors
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    QObject::connect(sliderRuntime, SIGNAL(sliderMoved(int)), this, SLOT(onRuntimeChanged(int)));
    QObject::connect(sliderBandwidth, SIGNAL(sliderMoved(int)), this, SLOT(onBandwidthChanged(int)));

    setLayout(layout);
}

void Client::onExitButtonClicked()
{
    this->close();
}

void Client::onStartButtonClicked()
{
    if(listening){
        tl->setColor(TrafficLight::green);
        listening = false;
        startButton->setText("Stop");

    }else{
        tl->setColor(TrafficLight::red);
        startButton->setText("Restart");
        listening = true;

    }

}

void Client::onRuntimeChanged(int value)
{
    fieldRuntime->setText(QString::number(value));
}

void Client::onBandwidthChanged(int value)
{
    fieldBandwidth->setText(QString::number(value));
}

