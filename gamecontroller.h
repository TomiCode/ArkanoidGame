/**
 * 
 * gamecontroller.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QEvent>
#include <QImage>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>

#include "gamepaddle.h"
#include "gameball.h"
#include "gameblock.h"
#include "gamecounter.h"
#include "gametypes.h"

class GameController : public QObject
{
  Q_OBJECT
public:
  explicit GameController(QGraphicsScene &scene, QObject *parent = 0);
  ~GameController();
  bool eventFilter(QObject *object, QEvent *event);

  void ballCollisions(GameBall *ball);
  void registerBall();
  void registerPoint(Arkanoid::GameSpecials special, float value, GameBall *ball);
  void createGameBlocks();
  void gamePause(bool resume = false);

public slots:
  void initGameWindow();
  void startNewGame();

private:
  QGraphicsScene &scene;
  QTimer *sceneTimer;
  GamePaddle *gamePaddle;
  GameCounter *gameCounter;
  int ballCount;
  QImage *blockAsset;
  bool gameStarted;

  bool keyboardController(QKeyEvent *keyEvent);
  QColor generateRandomColor();
  void clearGameScene();
};

#endif // GAMECONTROLLER_H
