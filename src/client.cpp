#include "client.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

Client::Client(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 480);
    QVBoxLayout *layout = new QVBoxLayout();

    QFont font;
    font.setBold(true);
    font.setPointSize(30);

    QLabel *label = new QLabel("Client Window");
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

void Client::onExitButtonClicked()
{
    this->close();
}

