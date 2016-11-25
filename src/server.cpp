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
#include <QComboBox>

Server::Server(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //IP address label
    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("10.22.0.160");
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
    label->adjustSize();

    //network interface selection
    networkInterface = new QComboBox();
    networkInterface->addItem("eth0");
    networkInterface->addItem("wlan0");

    //exit & start button
    QPushButton *exitButton = new QPushButton("Close");
    startButton = new QPushButton("Start");

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::red);

    //log window
    log = new QTextEdit();
    log->setReadOnly(true);
    log->setPlaceholderText("Log Ausgabe:");

    layout->addWidget(tl, 0, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(label, 0, 1);
    layout->addWidget(networkInterface, 0, 2);
    layout->addWidget(log, 1, 1, 1, 2);
    layout->addWidget(exitButton, 2, 2);
    layout->addWidget(startButton, 2, 1);

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));

    setLayout(layout);

    // create iperf interface in server mode
    this->iperfInterface = new IperfInterface("-s -u -p 5001");

    // connect logging slot to log text field append signal
    QObject::connect(this->iperfInterface, SIGNAL(logOutput(QString)), this->log, SLOT(append(QString)));

    // connect server started listening slot to set traffic light yellow signal
    QObject::connect(this->iperfInterface, SIGNAL(serverStartedListening()), this, SLOT(onSetTrafficLightYellow()));

    // connect server connection established slot to set traffic light green signal
    QObject::connect(this->iperfInterface, SIGNAL(connectionEstablished()), this, SLOT(onSetTrafficLightGreen()));
}

void Server::onExitButtonClicked()
{
    // if server window was closed, kill the iperf interface server
    this->iperfInterface->kill();
    this->close();
}

void Server::onStartButtonClicked()
{
    // clear the log text field
    this->log->clear();

    // check if iperf interface server is not already listening
    if (!this->iperfInterface->getIsServerListening()) {
        tl->setColor(TrafficLight::green);
        startButton->setText("Stop");

        // run iperf interface in server mode
        this->iperfInterface->run();
    } else {
        tl->setColor(TrafficLight::red);
        startButton->setText("Start");

        // kill iperf interface server
        this->iperfInterface->kill();

        // set iperf interface server listening to false
        this->iperfInterface->setServerIsListening(false);

        // set traffic light to red
        this->tl->setColor(TrafficLight::red);
    }

    QTextCursor c = log->textCursor();
    c.movePosition(QTextCursor::End);
    log->setTextCursor(c);
}

void Server::onSetTrafficLightRed() {
    this->tl->setColor(TrafficLight::red);
}

void Server::onSetTrafficLightYellow() {
    this->tl->setColor(TrafficLight::yellow);
}

void Server::onSetTrafficLightGreen() {
    this->tl->setColor(TrafficLight::green);
}
