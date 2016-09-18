/**
 * 
 * gamecounter.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "gamecounter.h"

GameCounter::GameCounter(float top, float width)
  : points(0),
    currentAplha(0),
    sceneWidth(width),
    messageUpdated(false),
    currentScreen(Arkanoid::ScreenPlaying),
    nextScreen(Arkanoid::ScreenWelcome),
    currentState(StateFadeOut),
    messagePosition(QPointF(this->sceneWidth / 2, top)),
    messageFont(QFont("Helvetica", 18)),
    messageColor(QColor(90, 90, 90, 0)),
    messageString("")
{
}

QRectF GameCounter::boundingRect() const
{
  return this->shape().boundingRect();
}

QPainterPath GameCounter::shape() const
{
  QPainterPath shape;
  shape.addText(0, 0, this->messageFont, this->messageString);
  return shape;
}

void GameCounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->save();
  painter->fillPath(this->shape(), QBrush(this->messageColor));
  painter->restore();
}

void GameCounter::advance(int phase)
{
  if (!phase)
    return;

  if (this->currentState == StateFadeIn) {
    if (this->currentAplha < 255) {
      currentAplha += 12;
      if (currentAplha > 255) {
        currentAplha = 255;
      }
      this->messageColor.setAlpha(this->currentAplha);
    } else {
      this->currentState = StateVisible;
    }
  } else if (this->currentState == StateFadeOut) {
    if (this->currentAplha > 0) {
      currentAplha -= 16;
      if (currentAplha < 0) {
        currentAplha = 0;
      }
      this->messageColor.setAlpha(this->currentAplha);
    } else {
      this->currentState = StateNone;
    }
  }

  this->updateScreenState();
  if (this->messagePosition.x() != ((this->sceneWidth / 2) - (this->boundingRect().width() / 2))) {
    this->messagePosition.setX(((this->sceneWidth / 2) - (this->boundingRect().width() / 2)));
    this->setPos(this->messagePosition);
  }
  if (this->currentState == StateFadeIn || this->currentState == StateFadeOut) {
    this->update(this->shape().boundingRect());
  }
}

void GameCounter::updateSceneWidth(float width)
{
  this->sceneWidth = width;
}

void GameCounter::updateScreenState()
{
  if (this->timeout >= 1 && this->currentState == StateVisible && this->currentScreen != Arkanoid::ScreenPlaying) {
    timeout--;

    if (this->timeout <= 1) {
      this->nextScreen = Arkanoid::ScreenPlaying;
      this->currentState = StateFadeOut;
      this->timeout = 0;
    }
  }
  else if (this->currentState == StateNone && this->nextScreen != Arkanoid::ScreenNoChange) {
    this->currentScreen = this->nextScreen;
    this->nextScreen = Arkanoid::ScreenNoChange;
    this->messageUpdated = false;
    this->updateScreenMessage();
    this->currentState = StateFadeIn;
  } else if (this->currentState == StateVisible && this->currentScreen == Arkanoid::ScreenPlaying) {
    this->updateScreenMessage();
  }
}

void GameCounter::updateScreenMessage()
{
  if (this->currentScreen == Arkanoid::ScreenPlaying) {
    this->messageString.sprintf("Punkty: %02d", this->points);
  } else if (this->currentScreen == Arkanoid::ScreenWelcome && !this->messageUpdated) {
    this->messageString.sprintf("Witaj w arkanoidzie!");
    this->messageUpdated = true;
  } else if (this->currentScreen == Arkanoid::ScreenComplete && !this->messageUpdated) {
    this->messageString.sprintf("Zwycięstwo! Suma punktów uzyskanych: %d", this->points);
    this->messageUpdated = true;
  } else if (this->currentScreen == Arkanoid::ScreenGameOver && !this->messageUpdated) {
    this->messageString.sprintf("Przegrałeś. Suma punktów uzyskanych: %d", this->points);
    this->messageUpdated = true;
  } else if (this->currentScreen == Arkanoid::ScreenBallSpeed && !this->messageUpdated) {
    this->messageString.sprintf("Piłka przyspieszyła %.1lf razy!", this->specialValue);
    this->messageUpdated = true;
  } else if (this->currentScreen == Arkanoid::ScreenPaddleSpeed && !this->messageUpdated) {
    this->messageString.sprintf("Paletka przyspieszyła o %1.0lf!", this->specialValue);
    this->messageUpdated = true;
  } else if (this->currentScreen == Arkanoid::ScreenPointMultiplayer && !this->messageUpdated) {
    this->messageString.sprintf("Liczba punktów %1.1lf razy zwiększona!!", this->specialValue);
    this->messageUpdated = true;
  }
}

void GameCounter::addPoints(int points)
{
  this->points += points;
}

void GameCounter::multiplyPoints(float points)
{
  this->points *= points;
}

void GameCounter::showScreen(int timeout, Arkanoid::GameScreen screen, float special)
{
  if (screen != Arkanoid::ScreenPlaying && timeout > 0) {
    this->timeout = timeout;
  } else {
    this->timeout = 0;
  }
  this->nextScreen   = screen;
  this->currentState = StateFadeOut;
  this->specialValue = special;
}
