/**
 * 
 * gameblock.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "gameblock.h"

GameBlock::GameBlock(QImage *block, QPointF position, Arkanoid::GameSpecials special, float value)
  : blockAsset(block),
    blockPosition(position),
    blockColor(Qt::white),
    blockSpecialValue(value),
    blockSpecial(special)
{
  this->setPos(position);
  this->setData(Arkanoid::GameObject, Arkanoid::GameBlock);
}

QRectF GameBlock::boundingRect() const
{
  return QRectF(QPointF(0, 0), this->blockAsset->size());
}

void GameBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->save();
  painter->drawImage(0, 0, *this->blockAsset);
  painter->setCompositionMode(QPainter::CompositionMode_Plus);
  painter->fillRect(this->blockAsset->rect(), this->blockColor);
  painter->restore();
}

Arkanoid::GameSpecials GameBlock::specialsBlock()
{
  return this->blockSpecial;
}

float GameBlock::specialsBlockValue()
{
  return this->blockSpecialValue;
}

void GameBlock::lowerSpecialsValue(float value)
{
  this->blockSpecialValue -= value;
}

void GameBlock::setBlockColor(QColor color)
{
  this->blockColor = color;
}

void GameBlock::darkenColor()
{
  this->blockColor = this->blockColor.darker(180);
}
