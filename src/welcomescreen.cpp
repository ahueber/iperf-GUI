#include "welcomescreen.h"
#include <QHBoxLayout>
#include <QPushButton>

WelcomeScreen::WelcomeScreen(QWidget *parent) : QWidget(parent)
{

    setMinimumSize(800, 480);

    QHBoxLayout *layout = new QHBoxLayout();

    QPushButton *serverButton = new QPushButton("Server");
    QPushButton *clientButton = new QPushButton("Client");
    QSize buttonSize(200, 200);
    serverButton->setFixedSize(buttonSize);
    clientButton->setFixedSize(buttonSize);

    layout->addWidget(serverButton);
    layout->addWidget(clientButton);

    setLayout(layout);
}

