#include "server.h"
#include "trafficlight.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QTextCursor>

Server::Server(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //IP address label
    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("192.168.1.37");
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
    label->adjustSize();

    //exit & start button
    QPushButton *exitButton = new QPushButton("Schliessen");
    startButton = new QPushButton("Starten");

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::yellow);

    //log window
    log = new QTextEdit();
    log->setReadOnly(true);
    log->setPlaceholderText("Log Ausgabe:");

    layout->addWidget(tl, 0, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(label, 0, 1);
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

        QString longtext;
        for(int i = 0; i < 100; i++){
            longtext.append("[  4]  0.0- 1.0 sec   1.3 MBytes  10.0 Mbits/sec  0.209 ms    1/  894 (0.11%)\n ");
        }


        log->insertPlainText(longtext);
    }else{
        tl->setColor(TrafficLight::red);
        startButton->setText("Restart");
        listening = true;
        log->insertPlainText("terminated");
    }
    QTextCursor c = log->textCursor();
    c.movePosition(QTextCursor::End);
    log->setTextCursor(c);
}

