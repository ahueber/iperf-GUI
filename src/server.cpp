#include "server.h"
#include "trafficlight.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>

Server::Server(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //window title
    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("Server Window");
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
    label->setMinimumSize(200, 200);
    label->adjustSize();

    //exit & start button
    QPushButton *exitButton = new QPushButton("Exit");
    startButton = new QPushButton("Start");

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::yellow);

    //log window
    QTextEdit *log = new QTextEdit();
    log->setReadOnly(true);
    log->setPlaceholderText("blubb");

    layout->addWidget(label, 0, 1);
    layout->addWidget(tl, 0, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(log, 1, 1, 1, 2);
    layout->addWidget(exitButton, 2, 2);
    layout->addWidget(startButton, 2, 1);

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));

    setLayout(layout);
}

void Server::onExitButtonClicked()
{
    this->close();
}

void Server::onStartButtonClicked()
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

