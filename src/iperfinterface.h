#ifndef IPERFINTERFACE_H
#define IPERFINTERFACE_H

#include <QObject>

class IperfInterface : public QProcess
{
public:
    IperfInterface();
};

#endif // IPERFINTERFACE_H