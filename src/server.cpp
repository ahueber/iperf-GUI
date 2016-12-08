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
#include <QMap>
#include <QDebug>

Server::Server(QWidget *parent) : QWidget(parent) {
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //IP address label
    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    this->networkInterfaceAddress = new QLabel("10.22.0.160");
    this->networkInterfaceAddress->setScaledContents(true);
    this->networkInterfaceAddress->setAlignment(Qt::AlignCenter);
    this->networkInterfaceAddress->setFont(font);
    this->networkInterfaceAddress->adjustSize();

    //network interface selection
    networkInterface = new QComboBox();

    //exit & start button
    QPushButton *exitButton = new QPushButton("Close");
    startButton = new QPushButton("Start");

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::red);

    //log window
    log = new QTextEdit();
    log->setReadOnly(true);
    log->setPlaceholderText("iperf3 Log output");

    layout->addWidget(tl, 0, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(this->networkInterfaceAddress, 0, 1);
    layout->addWidget(networkInterface, 0, 2);
    layout->addWidget(log, 1, 1, 1, 2);
    layout->addWidget(exitButton, 2, 2);
    layout->addWidget(startButton, 2, 1);

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    QObject::connect(this->networkInterface, SIGNAL(currentIndexChanged(int)), this, SLOT(onNetworkInterfaceDropdownChanged(int)));

    setLayout(layout);

    // create iperf interface in server mode
    this->iperfInterface = new IperfInterface("-s -p 5001");

    // TODO: On change event for interface dropdown implementation
    this->availableNetworkInterfaces = this->iperfInterface->getNetworkInterfaces();
    QMap<QString, QString>::iterator i;
    for (i = this->availableNetworkInterfaces.begin(); i != this->availableNetworkInterfaces.end(); ++i) {
        this->networkInterface->addItem(i.key());
    }

    // iperf interface signal & slot handling
    QObject::connect(this->iperfInterface, SIGNAL(logOutput(QString)), this->log, SLOT(setText(QString)));
    QObject::connect(this->iperfInterface, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(onProcessStateChanged(QProcess::ProcessState)));
    QObject::connect(this->iperfInterface, SIGNAL(connectionEstablished()), this, SLOT(onConnectionEstablished()));
    QObject::connect(this->iperfInterface, SIGNAL(connectionClosed()), this, SLOT(onConnectionClosed()));
}

void Server::setIsRunning() {
    if (this->iperfInterface->state() == QProcess::Running) {
        //this->log->setText("Server listening");
        this->tl->setColor(TrafficLight::green);
        this->startButton->setText("Stop");
        this->iperfInterface->setServerIsListening(true);
    }
}

void Server::setIsNotRunning() {
    if (this->iperfInterface->state() == QProcess::NotRunning) {
        //this->log->setText("Server not listening");
        this->tl->setColor(TrafficLight::red);
        this->startButton->setText("Start");
        this->iperfInterface->setServerIsListening(false);
    }
}

void Server::setIsRunningAndConnected() {
    if (this->iperfInterface->state() == QProcess::Running) {
        this->tl->setColor(TrafficLight::yellow);
    }
}

void Server::onExitButtonClicked() {
    this->setIsNotRunning();
    // if server window was closed, kill the iperf interface server
    this->iperfInterface->kill();
    this->close();
}

void Server::onStartButtonClicked() {
    // clear the log text field
    this->log->clear();

    // check if process is already running
    if (this->iperfInterface->state() == QProcess::NotRunning) {
        // run iperf interface in server mode
        this->iperfInterface->run();
    } else {
        // kill iperf interface server
        this->iperfInterface->kill();
    }

    QTextCursor c = log->textCursor();
    c.movePosition(QTextCursor::End);
    log->setTextCursor(c);
}

void Server::onNetworkInterfaceDropdownChanged(const int &index) {
    QString selectedNetworkInterfaceName = this->networkInterface->itemText(index);
    QString selectedNetworkInterfaceAddress = this->availableNetworkInterfaces.value(selectedNetworkInterfaceName);
    this->networkInterfaceAddress->setText(selectedNetworkInterfaceAddress);
}

void Server::onProcessStateChanged(const QProcess::ProcessState &newState) {
    switch (newState) {
        case QProcess::Running:
            this->setIsRunning();
            break;

        case QProcess::NotRunning:
            this->setIsNotRunning();
            break;

        default:
            break;
    }
}

void Server::onConnectionEstablished() {
    this->setIsRunningAndConnected();
}

void Server::onConnectionClosed() {
    this->setIsRunning();
}
