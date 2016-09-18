/**
 * 
 * maingame.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "maingame.h"
#include "ui_maingame.h"

MainGame::MainGame(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainGame),
  scene(new QGraphicsScene(this)),
  controller(new GameController(*scene, this)),
  saveDialog(new QFileDialog(this))
{
  this->ui->setupUi(this);

  /* OpenGl Widget initialization with VSync turned on.. of course Who likes tearing?! */
  QGLFormat glFormat(QGL::SampleBuffers | QGL::DirectRendering);
  glFormat.setSwapInterval(1);
  this->ui->gameGraphics->setViewport(new QGLWidget(glFormat, this));

  this->scene->setSceneRect(0, 0, ui->gameGraphics->size().width(), ui->gameGraphics->size().height());
  this->ui->gameGraphics->setScene(this->scene);

  this->saveDialog->setFileMode(QFileDialog::AnyFile);
  this->saveDialog->setAcceptMode(QFileDialog::AcceptSave);
  this->saveDialog->setNameFilter("Zdjęcie PNG (*.png)");
  this->saveDialog->setDefaultSuffix(".png");
  this->saveDialog->setWindowTitle("Zapisywanie SS'a gry...");

  connect(ui->act_exit,    SIGNAL(triggered(bool)), this,       SLOT(close()));
  connect(ui->act_newgame, SIGNAL(triggered(bool)), controller, SLOT(startNewGame()));
  connect(ui->act_screen,  SIGNAL(triggered(bool)), this,       SLOT(openSaveDialog()));
  connect(saveDialog,      SIGNAL(fileSelected(QString)), this, SLOT(saveGameScreen(QString)));
  connect(saveDialog, SIGNAL(rejected()), this, SLOT(resumeGame()));
  connect(saveDialog, SIGNAL(accepted()), this, SLOT(resumeGame()));

  QTimer::singleShot(50, Qt::CoarseTimer, this->controller, SLOT(initGameWindow()));
}

MainGame::~MainGame()
{
  delete ui;
  delete scene;
  delete controller;
  delete saveDialog;
}

void MainGame::openSaveDialog()
{
  this->controller->gamePause();
  this->saveDialog->show();
}

void MainGame::resumeGame()
{
  this->controller->gamePause(true);
}

void MainGame::saveGameScreen(QString file)
{
  if (file.isEmpty())
    return;

  QImage gameImage(this->ui->gameGraphics->sceneRect().size().toSize(), QImage::Format_ARGB32);
  QPainter gamePainter(&gameImage);

  gameImage.fill(Qt::transparent);
  gamePainter.setRenderHints(this->ui->gameGraphics->renderHints());
  this->scene->render(&gamePainter, QRectF(0, 0, gameImage.width(), gameImage.height()));
  gameImage.save(file, "PNG");
}
