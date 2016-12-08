#include "iperfinterface.h"

IperfInterface::IperfInterface(QString initialArguments, QString logPathAndFilename) {
    this->initialArguments = initialArguments;
    this->logPathAndFilename = logPathAndFilename;

    this->setProcessChannelMode(QProcess::MergedChannels);
    //QObject::connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(processReadyReadStandardOutput()));

    this->logFile = new QFile(this->logPathAndFilename);
    this->logFile->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    this->logFile->close();

    this->logFileWatcher = new QFileSystemWatcher(QStringList(this->logPathAndFilename));
    QObject::connect(this->logFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(processFileChanged(QString)));
}

IperfInterface::~IperfInterface() {
    if (this->isOpen()) {
        this->kill();
    }
}

QStringList IperfInterface::parseCombinedArgString(const QString &program) {
    QStringList args;
    QString tmp;
    int quoteCount = 0;
    bool inQuote = false;
    // handle quoting. tokens can be surrounded by double quotes
    // "hello world". three consecutive double quotes represent
    // the quote character itself.
    for (int i = 0; i < program.size(); ++i) {
        if (program.at(i) == QLatin1Char('"')) {
            ++quoteCount;
            if (quoteCount == 3) {
                // third consecutive quote
                quoteCount = 0;
                tmp += program.at(i);
            }
            continue;
        }
        if (quoteCount) {
            if (quoteCount == 1)
                inQuote = !inQuote;
            quoteCount = 0;
        }
        if (!inQuote && program.at(i).isSpace()) {
            if (!tmp.isEmpty()) {
                args += tmp;
                tmp.clear();
            }
        }
        else {
            tmp += program.at(i);
        }
    }
    if (!tmp.isEmpty())
        args += tmp;
    return args;
}

QString IperfInterface::getInitialArguments() {
    return this->initialArguments;
}

void IperfInterface::setInitialArguments(QString initialArguments) {
    this->initialArguments = initialArguments;
}

QString IperfInterface::getLogPathAndFilename() {
    return this->logPathAndFilename;
}

/*
void IperfInterface::setLogPathAndFilename(QString logPathAndFilename) {
    this->logPathAndFilename = logPathAndFilename;
}
*/

void IperfInterface::setServerIsListening(bool serverIsListening) {
    this->serverIsListening = serverIsListening;
}

bool IperfInterface::getIsServerListening() {
    return this->serverIsListening;
}

QMap<QString, QString> IperfInterface::getNetworkInterfaces() {
    QMap<QString, QString> networkInterfaces;
    try {
        foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
            foreach (const QNetworkAddressEntry &interfaceAddressEntry, interface.addressEntries()) {
                if (!interfaceAddressEntry.ip().isNull() && !interfaceAddressEntry.ip().isLoopback() && interfaceAddressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    networkInterfaces.insert(interface.name(), interfaceAddressEntry.ip().toString());
                }
            }
        }
    } catch (std::exception &e) {
        qDebug() << "Could not fetch network interface list";
    }
    return networkInterfaces;
}

void IperfInterface::run() {
    QStringList parsedArguments = this->parseCombinedArgString(QString(this->initialArguments).append(" --logfile ").append(this->logPathAndFilename));
    this->start(IPERF_PATH_AND_FILENAME, parsedArguments);
    //this->waitForReadyRead();
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

QString IperfInterface::getLastLine(const QString &text) {
    QStringList lines = text.split("\n");
    int linesCount = lines.size();
    QString lastLine("");
    while (lastLine.isEmpty()) {
        lastLine = lines.at(--linesCount);
    }
    return lastLine;
}

void IperfInterface::parseLogOutput(const QString &logOutput) {
    if (!this->clientConnected && logOutput.contains(QRegExp(MSG_CONNECTION_ESTABLISHED))) {
        emit this->connectionEstablished();
        this->clientConnected = true;
    } else if (this->clientConnected && logOutput.contains(QRegExp(MSG_CONNECTION_CLOSED))) {
        emit this->connectionClosed();
        emit this->logOutput(logOutput);
        this->clientConnected = false;
        this->clearLogFile();
    }
}

void IperfInterface::clearLogFile() {
    if (!this->logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    this->logFile->resize(0);
    this->logFile->close();
}

void IperfInterface::processFileChanged(const QString &) {
    if (!this->logFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString logFileContent = this->logFile->readAll();
    this->logFile->close();

    this->parseLogOutput(logFileContent);
    if (this->clientConnected) {
        emit this->logOutput(logFileContent);
    }

}
