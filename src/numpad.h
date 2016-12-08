/**
 * @file numpad.h
 * @brief Das Widget für die Nummern-Tastatur.
 *
 * Diese Klasse repräsentiert das Widget für die Nummern-Tastatur, welche für die
 * Eingabe der IP-Adresse benötigt wird. Das Widget wird von der Client-Klasse geöffnet.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>

class QPushButton;
class QLabel;
class Client;

/**
 * @brief Die NumPad-Klasse
 */
class NumPad : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnDot;
    QPushButton *btnDone;
    QPushButton *btnBksp;
    QLabel *panel;
    void addString(QString str);
public:
    /**
     * @brief Der NumPad-Konstruktor
     * @param c
     */
    explicit NumPad(Client *c);

    /**
     * @brief Das Client-Widget
     */
    Client *client;

signals:

public slots:
    /**
     * @brief Beim Klicken des Zero-Button aufgerufene Handler-Methode.
     */
    void onButtonZeroClicked();
    /**
     * @brief Beim Klicken des One-Button aufgerufene Handler-Methode.
     */
    void onButtonOneClicked();
    /**
     * @brief Beim Klicken des Two-Button aufgerufene Handler-Methode.
     */
    void onButtonTwoClicked();
    /**
     * @brief Beim Klicken des Three-Button aufgerufene Handler-Methode.
     */
    void onButtonThreeClicked();
    /**
     * @brief Beim Klicken des Four-Button aufgerufene Handler-Methode.
     */
    void onButtonFourClicked();
    /**
     * @brief Beim Klicken des Five-Button aufgerufene Handler-Methode.
     */
    void onButtonFiveClicked();
    /**
     * @brief Beim Klicken des Six-Button aufgerufene Handler-Methode.
     */
    void onButtonSixClicked();
    /**
     * @brief Beim Klicken des Seven-Button aufgerufene Handler-Methode.
     */
    void onButtonSevenClicked();
    /**
     * @brief Beim Klicken des Eight-Button aufgerufene Handler-Methode.
     */
    void onButtonEightClicked();
    /**
     * @brief Beim Klicken des Nine-Button aufgerufene Handler-Methode.
     */
    void onButtonNineClicked();
    /**
     * @brief Beim Klicken des Dot-Button aufgerufene Handler-Methode.
     */
    void onButtonDotClicked();
    /**
     * @brief Beim Klicken des Done-Button aufgerufene Handler-Methode.
     */
    void onButtonDoneClicked();
    /**
     * @brief Beim Klicken des Backspace-Button aufgerufene Handler-Methode.
     */
    void onButtonBkspClicked();
};

#endif // NUMPAD_H
