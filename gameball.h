/**
 * 
 * gameball.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/


#ifndef GAMEBALL_H
#define GAMEBALL_H

#include <QImage>
#include <QPainter>
#include <QGraphicsItem>

#include "gametypes.h"

class GameController;

class GameBall : public QGraphicsItem
{
public:
  GameBall(GameController &controller, QImage ball);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void advance(int phase);

  void ballVelocityDown(bool down);
  void ballVelocityRight(bool right);
  void multiplyBallVelocity(float velx, float vely);

private:
  GameController &controller;
  QPointF ballPosition;
  QPointF ballVelocity;
  QImage  ballImage;
};

#endif // GAMEBALL_H
