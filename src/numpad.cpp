#include "numpad.h"
#include "client.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFont>

NumPad::NumPad(Client *c) : client(c)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();

    panel = new QLabel();

    panel->setAlignment(Qt::AlignRight);
    panel->setMinimumHeight(100);
    panel->setStyleSheet("QLabel { font-size: 60px; background-color: #666666; color: #ffffff; }");
    panel->setText(client->getIP());

    QList<QPushButton*> buttonList;

    QFont font;
    font.setBold(true);
    font.setPointSize(20);

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

    QObject::connect(btn0, SIGNAL(clicked()), this, SLOT(onButtonZeroClicked()));
    QObject::connect(btn1, SIGNAL(clicked()), this, SLOT(onButtonOneClicked()));
    QObject::connect(btn2, SIGNAL(clicked()), this, SLOT(onButtonTwoClicked()));
    QObject::connect(btn3, SIGNAL(clicked()), this, SLOT(onButtonThreeClicked()));
    QObject::connect(btn4, SIGNAL(clicked()), this, SLOT(onButtonFourClicked()));
    QObject::connect(btn5, SIGNAL(clicked()), this, SLOT(onButtonFiveClicked()));
    QObject::connect(btn6, SIGNAL(clicked()), this, SLOT(onButtonSixClicked()));
    QObject::connect(btn7, SIGNAL(clicked()), this, SLOT(onButtonSevenClicked()));
    QObject::connect(btn8, SIGNAL(clicked()), this, SLOT(onButtonEightClicked()));
    QObject::connect(btn9, SIGNAL(clicked()), this, SLOT(onButtonNineClicked()));
    QObject::connect(btnDot, SIGNAL(clicked()), this, SLOT(onButtonDotClicked()));
    QObject::connect(btnDone, SIGNAL(clicked()), this, SLOT(onButtonDoneClicked()));
    QObject::connect(btnBksp, SIGNAL(clicked()), this, SLOT(onButtonBkspClicked()));

    setLayout(layout);
}

void NumPad::addString(QString str){
    QString text = panel->text();

    QStringList segments = text.split(".");
    int segmentCount = segments.size();
    QString lastSegment = segments.at(segmentCount - 1);

    // decimal point
    if (str == ".") {

        // max. 4 segments
        if (segmentCount > 3) {
            // do nothing
        } else if (lastSegment == "") {
            text += "0" + str;
        } else {
            text += str;
        }

    // number
    } else {

        if (lastSegment.size() > 2) {
            if (segmentCount == 4) {
                // do nothing
            } else {
                text += "." + str;
            }
        } else {
            text += str;
        }

    }

    // iterate through segments and validat/filter segment values
    QStringList strlist = text.split(".");
    for (int i = 0; i < strlist.size(); i++) {
        QString str = strlist.at(i);
        if (str.toInt() > 255) {
            strlist.replace(i, "255");
        } else if (str.toInt() > 0) {
            strlist.replace(i, str.remove(QRegExp("^[0]*")));
        } else {
           strlist.replace(i, "0");
        }
    }

    panel->setText(strlist.join("."));
}

void NumPad::onButtonZeroClicked()
{
    this->addString("0");
}

void NumPad::onButtonOneClicked()
{
    this->addString("1");
}

void NumPad::onButtonTwoClicked()
{
    this->addString("2");
}

void NumPad::onButtonThreeClicked()
{
    this->addString("3");
}

void NumPad::onButtonFourClicked()
{
    this->addString("4");
}

void NumPad::onButtonFiveClicked()
{
    this->addString("5");
}

void NumPad::onButtonSixClicked()
{
    this->addString("6");
}

void NumPad::onButtonSevenClicked()
{
    this->addString("7");
}

void NumPad::onButtonEightClicked()
{
    this->addString("8");
}

void NumPad::onButtonNineClicked()
{
    this->addString("9");
}

void NumPad::onButtonDotClicked()
{
    this->addString(".");
}

void NumPad::onButtonDoneClicked()
{
    client->setIP(panel->text());
    this->close();
}

void NumPad::onButtonBkspClicked()
{
    QString text = panel->text().mid(0, panel->text().size()-1);

    panel->setText(text);
}

