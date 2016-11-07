#include "welcomescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeScreen w;

    //w.show();
    w.showFullScreen();

    return a.exec();
}
