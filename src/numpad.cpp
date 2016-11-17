#include "numpad.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFont>

NumPad::NumPad(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();

    panel = new QLabel();
    panel->setAlignment(Qt::AlignRight);
    panel->setMinimumHeight(100);
    panel->setStyleSheet("QLabel { font-size: 24px; background-color: #666666; color: #ffffff; }");

    QList<QPushButton*> buttonList;

    QFont font;
    font.setBold(true);
    font.setPointSize(15);

    btn0 = new QPushButton("0");
    btn1 = new QPushButton("1");
    btn2 = new QPushButton("2");
    btn3 = new QPushButton("3");
    btn4 = new QPushButton("4");
    btn5 = new QPushButton("5");
    btn6 = new QPushButton("6");
    btn7 = new QPushButton("7");
    btn8 = new QPushButton("8");
    btn9 = new QPushButton("9");
    btnDot = new QPushButton(".");
    btnDone = new QPushButton("Done");
    btnBksp = new QPushButton("←");

    buttonList.append(btn0);
    buttonList.append(btn1);
    buttonList.append(btn2);
    buttonList.append(btn3);
    buttonList.append(btn4);
    buttonList.append(btn5);
    buttonList.append(btn6);
    buttonList.append(btn7);
    buttonList.append(btn8);
    buttonList.append(btn9);
    buttonList.append(btnDot);
    buttonList.append(btnDone);
    buttonList.append(btnBksp);

    for(auto b : buttonList){
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setFont(font);
    }

    layout->addWidget(panel, 0, 0, 1, 4);
    layout->addWidget(btn1, 1, 0);
    layout->addWidget(btn2, 1, 1);
    layout->addWidget(btn3, 1, 2);
    layout->addWidget(btn4, 2, 0);
    layout->addWidget(btn5, 2, 1);
    layout->addWidget(btn6, 2, 2);
    layout->addWidget(btn7, 3, 0);
    layout->addWidget(btn8, 3, 1);
    layout->addWidget(btn9, 3, 2);
    layout->addWidget(btn0, 4, 0, 1, 2);
    layout->addWidget(btnDot, 4, 2);
    layout->addWidget(btnBksp, 1, 3, 2, 1);
    layout->addWidget(btnDone, 3, 3, 2, 1);

    setLayout(layout);
}

