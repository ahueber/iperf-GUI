/**
 * @file trafficlight.h
 * @brief Das Widget für die Ampeldarstellung.
 *
 * Diese Klasse repräsentiert das Widget für die Ampeldarstellung, welche im
 * Client- und
 * Server-Widget eingesetzt wird.
 *
 * @author Andreas Hueber
 * @author Thomas Breuss
 */

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

/**
 * @brief Die TrafficLight-Klasse
 */
class TrafficLight : public QWidget {
  Q_OBJECT
private:
  QLabel *label;
  QHBoxLayout *layout;

public:
  /**
   * @brief Die drei Farben Grün, Rot, Gelb
   */
  enum color { green, red, yellow };
  /**
   * @brief Der TrafficLight-Konstruktor
   * @param parent
   */
  explicit TrafficLight(QWidget *parent = 0);
  /**
   * @brief Setzt die Farbe.
   * @param c
   */
  void setColor(color c);

signals:

public slots:
};

#endif // TRAFFICLIGHT_H
