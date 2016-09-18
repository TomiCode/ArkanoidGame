/**
 * 
 * gamepaddle.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "gamepaddle.h"

GamePaddle::GamePaddle(QImage paddleAsset)
  : paddleImage(paddleAsset),
    paddlePosition(QPointF(0, 0)),
    paddleMove(MoveNone),
    paddleMaximumX(0),
    paddleSpeed(1)
{
  this->setPos(this->paddlePosition);
  this->setData(Arkanoid::GameObject, Arkanoid::GamePaddle);
}

QRectF GamePaddle::boundingRect() const
{
  return QRectF(QPointF(0, 0), this->paddleImage.size());
}

void GamePaddle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->save();
  painter->drawImage(0, 0, this->paddleImage);
  painter->restore();
}

void GamePaddle::advance(int phase)
{
  if (!phase)
    return;

  if (this->paddleMove == MoveNone)
    return;

  if (this->paddleMove == MoveLeft && this->paddlePosition.x() > 0) {
    this->paddlePosition.rx() -= (this->paddleSpeed * 5.2f);
  }
  else if (this->paddleMove == MoveRight && this->paddlePosition.x() < this->paddleMaximumX) {
    this->paddlePosition.rx() += (this->paddleSpeed * 5.2f);
  }
  else if (this->paddleMove != MoveNone) {
    this->paddleMove = MoveNone;
  }

  if (this->paddlePosition.x() < 0) {
    this->paddlePosition.setX(0);
  } else if (this->paddlePosition.x() > this->paddleMaximumX) {
    this->paddlePosition.setX(paddleMaximumX);
  }

  this->setPos(this->paddlePosition);
}

void GamePaddle::updatePaddlePosition(QPointF position, int maxX)
{
  this->paddlePosition = position;
  this->paddlePosition.ry() -= (this->paddleImage.height() * 2);
  this->paddlePosition.rx() -= (this->paddleImage.width() / 2);
  this->setPos(this->paddlePosition);
  this->paddleMaximumX = (maxX - this->paddleImage.width());
}

void GamePaddle::changePaddleMove(PaddleMovement move)
{
  this->paddleMove = move;
}

void GamePaddle::updatePaddleSpeed(float speed)
{
  this->paddleSpeed = speed;
}

void GamePaddle::addPaddleSpeed(float speed)
{
  this->paddleSpeed += speed;
}
