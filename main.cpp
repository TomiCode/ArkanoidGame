/**
 * 
 * main.cpp
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#include "maingame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  qsrand(time(NULL));

  QApplication a(argc, argv);
  MainGame w;
  w.show();

  return a.exec();
}
