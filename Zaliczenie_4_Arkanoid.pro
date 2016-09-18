#-------------------------------------------------
#
# Project created by QtCreator 2015-10-31T12:00:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zaliczenie_4_Arkanoid
TEMPLATE = app


SOURCES += main.cpp\
        maingame.cpp \
    gamecontroller.cpp \
    gamepaddle.cpp \
    gameball.cpp \
    gameblock.cpp \
    gamecounter.cpp

HEADERS  += maingame.h \
    gamecontroller.h \
    gamepaddle.h \
    gameball.h \
    gametypes.h \
    gameblock.h \
    gamecounter.h

FORMS    += maingame.ui

RESOURCES += \
    gameassets.qrc
