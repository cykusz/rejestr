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
    SqlConnectionController.cpp \
    data/DataStructure.cpp \
    data/police_station/PoliceStationTableModel.cpp \
    PoliceStationModel.cpp \
    TestWidget.cpp \
    widgets/RejestrTableView.cpp

HEADERS  += MainWindow.h \
    core/sql/SqlConnectionObserver.h \
    SqlConnectionController.h \
    data/DataStructure.h \
    data/police_station/PoliceStationTableModel.h \
    PoliceStationModel.h \
    TestWidget.h \
    widgets/RejestrTableView.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
