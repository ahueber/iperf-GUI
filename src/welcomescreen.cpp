#include "welcomescreen.h"
#include "client.h"
#include "server.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

WelcomeScreen::WelcomeScreen(QWidget *parent) : QWidget(parent)
{

    setMinimumSize(800, 480);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    //create server & client buttons
    QPushButton *serverButton = new QPushButton("Server");
    QPushButton *clientButton = new QPushButton("Client");
    QSize buttonSize(200, 200);
    serverButton->setFixedSize(buttonSize);
    clientButton->setFixedSize(buttonSize);

    //add buttons to horizontal layout
    buttonsLayout->addWidget(serverButton);
    buttonsLayout->addSpacing(200);
    buttonsLayout->addWidget(clientButton);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    //create exit button
    QPushButton *exitButton = new QPushButton("Exit");

    //connect buttons

    QObject::connect(clientButton, SIGNAL(clicked()), this, SLOT(onClientButtonClicked()));
    QObject::connect(serverButton, SIGNAL(clicked()), this, SLOT(onServerButtonClicked()));
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));

    vLayout->addLayout(buttonsLayout);
    vLayout->addWidget(exitButton);

    setLayout(vLayout);
}

void WelcomeScreen::onClientButtonClicked()
{
    Client *c = new Client();
    //c->show();
    c->showFullScreen();
}

void WelcomeScreen::onServerButtonClicked()
{
    Server *s = new Server();
    s->showFullScreen();
}

void WelcomeScreen::onExitButtonClicked()
{
    this->close();
}

