/**
 * 
 * gameball.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/


#include "gameball.h"
#include "gamecontroller.h"

GameBall::GameBall(GameController &controller, QImage ball)
  : controller(controller),
    ballPosition(QPointF(320, 350)),
    ballVelocity(QPointF(2, -2)),
    ballImage(ball)
{
  this->setPos(this->ballPosition);
  this->setData(Arkanoid::GameObject, Arkanoid::GameBall);
  this->controller.registerBall();
}

QRectF GameBall::boundingRect() const
{
  return QRectF(QPointF(0, 0), this->ballImage.size());
}

void GameBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->save();
  painter->drawImage(0, 0, this->ballImage);
  painter->restore();
}

void GameBall::advance(int phase)
{
  if (!phase)
    return;

  if (this->ballVelocity.isNull())
    return;

  this->ballPosition += this->ballVelocity;
  this->setPos(this->ballPosition);

  this->controller.ballCollisions(this);
}

void GameBall::ballVelocityDown(bool down)
{
  if ((down && this->ballVelocity.y() < 0) || (!down && this->ballVelocity.y() > 0)) {
    this->ballVelocity.ry() *= -1;
  }
}

void GameBall::ballVelocityRight(bool right)
{
  if ((right && this->ballVelocity.x() < 0) || (!right && this->ballVelocity.x() > 0)) {
    this->ballVelocity.rx() *= -1;
  }
}

void GameBall::multiplyBallVelocity(float velx, float vely)
{
  if (abs(this->ballVelocity.x() * velx) <= 8) {
    this->ballVelocity.rx() *= velx;
  }
  if (abs(this->ballVelocity.y() * vely) <= 8) {
    this->ballVelocity.ry() *= vely;
  }
}
