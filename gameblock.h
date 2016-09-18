/**
 * 
 * gameblock.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

#include <QImage>
#include <QPainter>
#include <QGraphicsItem>

#include "gametypes.h"

class GameBlock : public QGraphicsItem
{
public:
  GameBlock(QImage *block, QPointF position, Arkanoid::GameSpecials special = Arkanoid::GameSpecialNone, float value = 1.0f);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  Arkanoid::GameSpecials specialsBlock();
  float specialsBlockValue();
  void  lowerSpecialsValue(float value);
  void  setBlockColor(QColor color);
  void  darkenColor();

private:
  QImage *blockAsset;
  QPointF blockPosition;
  QColor  blockColor;
  float   blockSpecialValue;
  Arkanoid::GameSpecials blockSpecial;

};

#endif // GAMEBLOCK_H
