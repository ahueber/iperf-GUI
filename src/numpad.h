#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>

class QPushButton;
class QLabel;
class Client;

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
    void addString(QString str);
public:
    explicit NumPad(Client *c);
    Client *client;


signals:

public slots:
    void onButtonZeroClicked();
    void onButtonOneClicked();
    void onButtonTwoClicked();
    void onButtonThreeClicked();
    void onButtonFourClicked();
    void onButtonFiveClicked();
    void onButtonSixClicked();
    void onButtonSevenClicked();
    void onButtonEightClicked();
    void onButtonNineClicked();
    void onButtonDotClicked();
    void onButtonDoneClicked();
    void onButtonBkspClicked();
};

#endif // NUMPAD_H
