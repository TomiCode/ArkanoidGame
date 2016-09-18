/**
 * 
 * gamecounter.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QPropertyAnimation>

#include "gametypes.h"

class GameCounter : public QGraphicsItem
{
public:

  enum ScreenState {
    StateNone,
    StateFadeIn,
    StateFadeOut,
    StateVisible
  };

  GameCounter(float top, float width);

  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void advance(int phase);

  void updateSceneWidth(float width);
  void showScreen(int timeout, Arkanoid::GameScreen screen, float special = 0.0f);

  void addPoints(int points);
  void multiplyPoints(float points);

private:
  int   timeout;
  int   points;
  int   currentAplha;
  float sceneWidth;
  bool  messageUpdated;

  Arkanoid::GameScreen currentScreen;
  Arkanoid::GameScreen nextScreen;
  ScreenState  currentState;

  QPointF messagePosition;
  QFont   messageFont;
  QColor  messageColor;
  QString messageString;

  float   specialValue;

  void updateScreenState();
  void updateScreenMessage();
};

#endif // GAMECOUNTER_H
