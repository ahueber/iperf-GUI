#include "clientinterface.h"

ClientInterface::ClientInterface(QObject *parent) : QObject(parent) {
    this->iperfPathAndFilename = QString("/usr/bin/iperf");
    this->iperfProcess = new QProcess(parent);
    connect(this->iperfProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(processReadyReadStandardOutput()));
    //connect(this->iperfProcess, SIGNAL(readyReadStandardError()), this, SLOT(processReadyReadStandardError()));
    this->iperfProcess->setProcessChannelMode(QProcess::MergedChannels);
}

ClientInterface::~ClientInterface() {
    this->iperfProcess->close();
    delete [] this->iperfProcess;
}

void ClientInterface::setCommandLineArguments(QString commandLineArguments) {
    this->commandLineArguments = commandLineArguments;
}

QStringList ClientInterface::parseCommandLineArguments() {
    QStringList arguments;
    for (QString argument: this->commandLineArguments.split("-", QString::SkipEmptyParts)) {
        if (argument.at(argument.length() - 1) == QString(" "))
            argument = argument.left(argument.length() - 1);
        arguments << QString("-").append(argument);
    }
    return arguments;
}

bool ClientInterface::run() {
    this->iperfProcess->start(this->iperfPathAndFilename, this->parseCommandLineArguments());
    return false;
}

bool ClientInterface::stop() {
    return false;
}

void ClientInterface::processReadyReadStandardOutput() {
    qDebug() << this->iperfProcess->readAllStandardOutput();
}

void ClientInterface::processReadyReadStandardError() {

}
