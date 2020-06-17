
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mazemap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interface.cpp \
    _Maze.cpp \
    AI.cpp

HEADERS  += mainwindow.h \
    interface.h \
    _Maze.h \
    AI.h \
    Global.h

FORMS    +=

RESOURCES += \
    sources.qrc
QT += multimedia
CONFIG += resources_big
RC_ICONS = Maze&Dungeon1.ico
