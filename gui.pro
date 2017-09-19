#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T22:20:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    token.cpp \
    plagiarismThread.cpp

HEADERS  += widget.h \
    token.h \
    plagiarismThread.h

FORMS    += widget.ui
