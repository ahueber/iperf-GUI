#include "server.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

Server::Server(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(800, 480);
    QVBoxLayout *layout = new QVBoxLayout();

    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("Server Window");
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
    label->setMinimumSize(200, 200);

    QPushButton *exitButton = new QPushButton("Exit");

    layout->addWidget(label);
    layout->addWidget(exitButton);

    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));

    setLayout(layout);
}

void Server::onExitButtonClicked()
{
    this->close();
}

