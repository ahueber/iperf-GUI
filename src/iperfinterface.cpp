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
    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        // only use network interfaces which are up and running
        if (interface.IsUp && interface.IsRunning) {
            // get interface name
            QString interfaceName = interface.name();

            // exclude loopback interface
            if (interfaceName != "lo") {
                // check if there are addresses assigned
                if (interface.addressEntries().size() > 0) {
                    // get the primary ip address of the network interface
                    try {
                        // filter ipv4 addresses
                        QHostAddress interfaceAddress = interface.addressEntries().first().ip();
                        if (interfaceAddress.protocol() == QAbstractSocket::IPv4Protocol) {
                            networkInterfaces.insert(interfaceName, interfaceAddress.toString());
                        }
                    } catch (std::exception &e) {
                        qDebug() << "Could not fetch first ip address of network interface " << interface.name();
                    }
                }
            }
        }
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

void IperfInterface::processFileChanged(const QString &) {
    if (!this->logFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    /*
    QTextStream in(this->logFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        emit this->logOutput(line);
    }
    */

    emit this->logOutput(this->logFile->readAll());

    this->logFile->close();
}
