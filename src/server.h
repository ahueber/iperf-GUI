#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class TrafficLight;
class QPushButton;
class QTextEdit;

class Server : public QWidget
{
    Q_OBJECT

private:
    bool listening;
    TrafficLight *tl;
    QPushButton *startButton;
    QTextEdit *log;

public:
    explicit Server(QWidget *parent = 0);

signals:

public slots:
    void onExitButtonClicked();
    void onStartButtonClicked();
};

#endif // SERVER_H
