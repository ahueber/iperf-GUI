/**
 * @file welcomescreen.h
 * @brief Das Widget für den Startbildschirm.
 *
 * Diese Klasse repräsentiert das Widget für den Startbildschirm der Applikation.
 * Dieses Widget wird von der main-Klasse aufgerufen.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>

/**
 * @brief Die WelcomeScreen-Klasse
 */
class WelcomeScreen : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Der WelcomeScreen-Konstruktor
     * @param parent
     */
    explicit WelcomeScreen(QWidget *parent = 0);

signals:

public slots:
    /**
     * @brief Beim Klicken des Client-Button aufgerufene Handler-Methode.
     */
    void onClientButtonClicked();
    /**
     * @brief Beim Klicken des Server-Button aufgerufene Handler-Methode.
     */
    void onServerButtonClicked();
    /**
     * @brief Beim Klicken des Beenden-Button aufgerufene Handler-Methode.
     */
    void onExitButtonClicked();
};

#endif // WELCOMESCREEN_H
