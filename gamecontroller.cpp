/**
 * 
 * gamecontroller.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "gamecontroller.h"

#define COLLIDE_OFFSET 6
#define BLOCKS_OFFSET  38

GameController::GameController(QGraphicsScene &scene, QObject *parent)
  : QObject(parent),
    scene(scene),
    sceneTimer(new QTimer(this)),
    gamePaddle(new GamePaddle(QImage(":/game/assets/paddleBlu.png"))),
    gameCounter(new GameCounter(26, 100)),
    ballCount(0),
    blockAsset(new QImage(":/game/assets/blockGrey.png")),
    gameStarted(false)
{
  connect(this->sceneTimer, SIGNAL(timeout()), &this->scene, SLOT(advance()));
  this->sceneTimer->start(1000 / 33);
  this->scene.addItem(this->gameCounter);
}

GameController::~GameController()
{
  delete this->sceneTimer;
  delete this->blockAsset;
}

void GameController::startNewGame()
{
  if (this->gameStarted) {
    this->clearGameScene();
  }
  this->gameCounter->multiplyPoints(0);
  this->gamePaddle->updatePaddlePosition(QPointF(this->scene.width() / 2, this->scene.height()), this->scene.width());
  this->gamePaddle->updatePaddleSpeed(1);

  this->scene.installEventFilter(this);
  this->scene.addItem(this->gamePaddle);
  this->scene.addItem(new GameBall(*this, QImage(":/game/assets/ballBlue.png")));

  this->gameStarted = true;
  this->createGameBlocks();
  this->gameCounter->showScreen(0, Arkanoid::ScreenPlaying);
}

void GameController::clearGameScene()
{
  this->ballCount = 0;
  this->scene.removeItem(this->gamePaddle);
  this->scene.removeItem(this->gameCounter);

  this->scene.clear();
  this->gameCounter->multiplyPoints(0);
  this->scene.addItem(this->gameCounter);
}

void GameController::initGameWindow()
{
  this->gameCounter->updateSceneWidth(this->scene.width());
}

void GameController::registerBall()
{
  this->ballCount++;
}

void GameController::createGameBlocks()
{
  QColor rowColor1;
  QColor rowColor2;
  bool   pairs;
  bool   special;
  GameBlock *newBlock;

  for (int i = 0; i < (this->blockAsset->height() * 6); i += this->blockAsset->height())
  {
    rowColor1 = this->generateRandomColor();
    rowColor2 = this->generateRandomColor();
    pairs = ((qrand() % 100) > 80) ? true : false;

    for(int j = 0; j < this->scene.width(); j += this->blockAsset->width())
    {
      if (special) {
        special = false;
      }

      if (qrand() % 100 > 90) {
        newBlock = new GameBlock(this->blockAsset, QPointF(j, i + BLOCKS_OFFSET), (Arkanoid::GameSpecials)((qrand() % 3) + 1), ((float)(qrand() % 100)) / 50.0f);
        newBlock->setBlockColor(Qt::black);
        special = true;
      } else if (qrand() % 100 > 65) {
        newBlock = new GameBlock(this->blockAsset, QPointF(j, i + BLOCKS_OFFSET), Arkanoid::GameSpecialDurability, 2);
      } else {
        newBlock = new GameBlock(this->blockAsset, QPointF(j, i + BLOCKS_OFFSET));
      }
      if (!special) {
        if (pairs && (j % 256 >= 127)) {
          newBlock->setBlockColor(rowColor2);
        } else {
          newBlock->setBlockColor(rowColor1);
        }
      }
      this->scene.addItem(newBlock);
    }
  }
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
  if (this->gameStarted && (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)) {
    if (this->keyboardController((QKeyEvent *)event)) {
      return true;
    }
  }
  return QObject::eventFilter(object, event);
}

bool GameController::keyboardController(QKeyEvent *keyEvent)
{
  bool keyRelease = keyEvent->type() == QKeyEvent::KeyRelease ? true : false;
  if (!keyRelease && keyEvent->type() != QKeyEvent::KeyPress) {
    return false;
  }

  if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_A) {
    this->gamePaddle->changePaddleMove(keyRelease ? GamePaddle::MoveNone : GamePaddle::MoveLeft);
  }
  else if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_D) {
    this->gamePaddle->changePaddleMove(keyRelease ? GamePaddle::MoveNone : GamePaddle::MoveRight);
  }
  return true;
}

void GameController::ballCollisions(GameBall *ball)
{
  QList <QGraphicsItem *> collidingItem = this->scene.collidingItems(ball);

  /* Królu approved! */
  if (!collidingItem.isEmpty()) {
    foreach(QGraphicsItem *i, collidingItem) {
      if (i->data(Arkanoid::GameObject) == Arkanoid::GamePaddle) {
        if (ball->pos().y() - i->pos().y() <= -ball->boundingRect().height() + 12) {
          ball->ballVelocityDown(false);
          if (ball->x() < i->x() + 8) {
            ball->multiplyBallVelocity(1.078f, 1.02f);
            ball->ballVelocityRight(false);
          } else if (ball->x() > (i->x() + i->boundingRect().width() - ball->boundingRect().width() - 8)) {
            ball->multiplyBallVelocity(1.078f, 1.02f);
            ball->ballVelocityRight(true);
          } else {
            ball->multiplyBallVelocity(1, 1.064f);
          }
        }
      } else if (i->data(Arkanoid::GameObject) == Arkanoid::GameBlock) {
        if ((i->x() + i->boundingRect().width() - COLLIDE_OFFSET) < ball->x()) {
          ball->ballVelocityRight(true);
        }
        else if ((i->x() + COLLIDE_OFFSET) > (ball->x() + ball->boundingRect().width())) {
          ball->ballVelocityRight(false);
        }
        else if ((i->y() + i->boundingRect().height() - COLLIDE_OFFSET) < ball->y()) {
          ball->ballVelocityDown(true);
        }
        else if ((i->y() + COLLIDE_OFFSET) > ball->y()) {
          ball->ballVelocityDown(false);
        }

        GameBlock *block = (GameBlock *)i;
        if (block->specialsBlock() != Arkanoid::GameSpecialDurability
            || (block->specialsBlock() == Arkanoid::GameSpecialDurability && block->specialsBlockValue() == 1)) {
          this->registerPoint(block->specialsBlock(), block->specialsBlockValue(), ball);
          this->scene.removeItem(i);
          delete i;
        } else {
          if (block->specialsBlockValue() > 1) {
            block->lowerSpecialsValue(1);
            block->darkenColor();
          }
        }
      }
    }
  }

  if (ball->pos().x() >= (this->scene.width() - ball->boundingRect().width())) {
    ball->ballVelocityRight(false);
  } else if (ball->pos().y() <= 0) {
    ball->ballVelocityDown(true);
  } else if (ball->pos().x() <= 0) {
    ball->ballVelocityRight(true);
  }
  else if(ball->pos().y() >= this->scene.height()) {
    if (this->ballCount > 1) {
      this->ballCount--;
    } else {
      this->gameCounter->showScreen(0, Arkanoid::ScreenGameOver);
      this->gamePaddle->changePaddleMove(GamePaddle::MoveNone);
      this->scene.removeEventFilter(this);
    }
    this->scene.removeItem(ball);
    delete ball;
    return;
  }

  foreach(QGraphicsItem *i, this->scene.items()) {
    if (i->data(Arkanoid::GameObject) == Arkanoid::GameBlock) {
      return;
    }
  }
  this->scene.removeItem(ball);
  delete ball;
  this->gameCounter->showScreen(0, Arkanoid::ScreenComplete);
}

void GameController::registerPoint(Arkanoid::GameSpecials special, float value, GameBall *ball)
{
  if (special == Arkanoid::GameSpecialNone || special == Arkanoid::GameSpecialDurability) {
    this->gameCounter->addPoints(value);
  } else if (special == Arkanoid::GameSpecialBallSpeed) {
    ball->multiplyBallVelocity(value, value);
    this->gameCounter->showScreen(30, Arkanoid::ScreenBallSpeed, value);
  } else if (special == Arkanoid::GameSpecialPaddleSpeed) {
    this->gamePaddle->addPaddleSpeed(value);
    this->gameCounter->showScreen(30, Arkanoid::ScreenPaddleSpeed, value);
  } else if (special == Arkanoid::GameSpecialPoints) {
    this->gameCounter->multiplyPoints(value);
    this->gameCounter->showScreen(30, Arkanoid::ScreenPointMultiplayer, value);
  }
}

QColor GameController::generateRandomColor()
{
  return QColor::fromHsv((qrand() % 360), 180, 72);
}

void GameController::gamePause(bool resume)
{
  if (resume) {
    this->sceneTimer->start();
  } else {
    this->sceneTimer->stop();
  }
}
