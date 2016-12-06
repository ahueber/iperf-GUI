/**
 * @file main.cpp
 * @brief The main file of this project.
 *
 * This is the main file and entry script of the project "iperf GUI".
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 * @author Tobias Merz
 */

#include "welcomescreen.h"
#include <QApplication>
#include <QSettings>
#include <QFile>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // See: http://stackoverflow.com/questions/30606306/using-qsettings-in-a-global-static-class
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("HF-ICT");
    QApplication::setOrganizationDomain("hf-ict.ch");
    QApplication::setApplicationName("IPERF-GUI");

    QSettings settings;
    if (!QFile(settings.fileName()).exists()) {
        settings.setValue("default.runtime", 30);
        settings.setValue("default.bandwidth", 10);
        // add additional config settings here
    }

    WelcomeScreen w;
    w.showFullScreen();

    return a.exec();
}
