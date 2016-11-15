#include "server.h"
#include "trafficlight.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QTextEdit>

Server::Server(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();

    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("Server Window");
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
    label->setMinimumSize(200, 200);
    label->adjustSize();

    QPushButton *exitButton = new QPushButton("Exit");

    TrafficLight *tl = new TrafficLight();

    QTextEdit *log = new QTextEdit();
    log->setReadOnly(true);
    log->setPlaceholderText("blubb");

    layout->addWidget(label, 0, 1);
    layout->addWidget(tl, 0, 0, 2, 1, Qt::AlignCenter);
    layout->addWidget(log, 1, 1);
    layout->addWidget(exitButton, 2, 1);

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));

    setLayout(layout);
}

void Server::onExitButtonClicked()
{
    this->close();
}

