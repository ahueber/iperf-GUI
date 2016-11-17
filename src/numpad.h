#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>

class QPushButton;
class QLabel;

class NumPad : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnDot;
    QPushButton *btnDone;
    QPushButton *btnBksp;
    QLabel *panel;
public:
    explicit NumPad(QWidget *parent = 0);

signals:

public slots:
};

#endif // NUMPAD_H
