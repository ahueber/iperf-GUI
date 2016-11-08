#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
};

#endif // SERVER_H
