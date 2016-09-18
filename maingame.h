/**
 * 
 * maingame.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef MAINGAME_H
#define MAINGAME_H

#include <QImage>
#include <QGLWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>

#include "gamecontroller.h"

namespace Ui {
  class MainGame;
}

class MainGame : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainGame(QWidget *parent = 0);
  ~MainGame();

private:
  Ui::MainGame *ui;
  QGraphicsScene *scene;
  GameController *controller;
  QFileDialog *saveDialog;

private slots:
  void openSaveDialog();
  void resumeGame();
  void saveGameScreen(QString file);
};

#endif // MAINGAME_H
