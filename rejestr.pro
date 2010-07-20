#-------------------------------------------------
#
# Project created by QtCreator 2010-07-19T22:06:15
#
#-------------------------------------------------

QT       += core gui sql

TARGET = rejestr
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    core/sql/SqlConnectionObserver.cpp \
    SqlConnectionController.cpp

HEADERS  += MainWindow.h \
    core/sql/SqlConnectionObserver.h \
    SqlConnectionController.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
