#include "iperfinterface.h"

IperfInterface::IperfInterface(QString initialArguments) {
    this->initialArguments = initialArguments;

    this->setProcessChannelMode(QProcess::MergedChannels);
    QObject::connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(processReadyReadStandardOutput()));
}

IperfInterface::~IperfInterface() {
    if (this->isOpen()) {
        this->kill();
    }
}

QStringList IperfInterface::parseArguments(QString arguments) {
    QStringList parsedArguments;
    for (QString argument: arguments.split("-", QString::SkipEmptyParts)) {
        if (argument.at(argument.length() - 1) == QString(" "))
            argument = argument.left(argument.length() - 1);
        parsedArguments << QString("-").append(argument);
    }
    return parsedArguments;
}

QString IperfInterface::getInitialArguments() {
    return this->initialArguments;
}

void IperfInterface::setInitialArguments(QString initialArguments) {
    this->initialArguments = initialArguments;
}

void IperfInterface::setServerIsListening(bool serverIsListening) {
    this->serverIsListening = serverIsListening;
}

bool IperfInterface::getIsServerListening() {
    return this->serverIsListening;
}

void IperfInterface::run() {
    QStringList parsedArguments = this->parseArguments(this->initialArguments);
    this->start(IPERF_PATH_AND_FILENAME, parsedArguments);
    this->waitForReadyRead();
}

void IperfInterface::processReadyReadStandardOutput() {
    QString rawOutput = QString(this->readAllStandardOutput());

    if (rawOutput.contains(QRegExp(MSG_SERVER_LISTENING))) {
        this->serverIsListening = true;
        emit this->serverStartedListening();
    }

    if (rawOutput.contains(QRegExp(MSG_CONNECTION_ESTABLISHED))) {
        emit this->connectionEstablished();
    }

    QStringList lines = rawOutput.split("\n");
    foreach (QString line, lines) {
        emit this->logOutput(line);
    }
}
