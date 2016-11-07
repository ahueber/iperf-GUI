#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
};

#endif // CLIENT_H
