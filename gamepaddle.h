/**
 * 
 * gamepaddle.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef GAMEPADDLE_H
#define GAMEPADDLE_H

#include <QImage>
#include <QPainter>
#include <QGraphicsItem>

#include "gametypes.h"

class GamePaddle : public QGraphicsItem
{
public:

  enum PaddleMovement {
    MoveNone  = 0,
    MoveLeft  = 1,
    MoveRight = 2
  };

  GamePaddle(QImage paddleAsset);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void advance(int phase);

  void updatePaddlePosition(QPointF position, int maxX);
  void changePaddleMove(PaddleMovement move);
  void updatePaddleSpeed(float speed);
  void addPaddleSpeed(float speed);
private:
  QImage  paddleImage;
  QPointF paddlePosition;
  PaddleMovement paddleMove;
  int     paddleMaximumX;
  float   paddleSpeed;
};

#endif // GAMEPADDLE_H
