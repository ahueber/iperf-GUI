/**
 * @file main.cpp
 * @brief Die main-Datei dieses Projekts.
 *
 * Das ist die Hauptdatei und Eingangsscript des Projekt "iperf GUI".
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 * @author Tobias Merz
 */

#include "welcomescreen.h"
#include <QApplication>
#include <QFile>
#include <QSettings>

/**
 * @brief Die main-Methode für das Projekt.
 * @param argc Der Grösse des Argumente-Arrays
 * @param argv Das Argumente-Array
 * @return
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // See:
  // http://stackoverflow.com/questions/30606306/using-qsettings-in-a-global-static-class
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
  w.show();

  return a.exec();
}
