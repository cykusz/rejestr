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
    PoliceStationModel.cpp \
    TestWidget.cpp \
    widgets/RejestrTableView.cpp \
    model/RejestrTableModel.cpp \
    model/ModelInterface.cpp \
    model/delegates/PoliceStationItemDelegate.cpp

HEADERS  += MainWindow.h \
    core/sql/SqlConnectionObserver.h \
    SqlConnectionController.h \
    data/DataStructure.h \
    PoliceStationModel.h \
    TestWidget.h \
    widgets/RejestrTableView.h \
    model/ModelInterface.h \
    model/RejestrTableModel.h \
    model/delegates/PoliceStationItemDelegate.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
