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
    widgets/RejestrTableView.cpp \
    model/RejestrTableModel.cpp \
    model/ModelInterface.cpp \
    policestation/PoliceStationItemDelegate.cpp \
    policestation/PoliceStationModel.cpp \
    model/AbstractModel.cpp

HEADERS  += MainWindow.h \
    core/sql/SqlConnectionObserver.h \
    SqlConnectionController.h \
    data/DataStructure.h \
    widgets/RejestrTableView.h \
    model/ModelInterface.h \
    model/RejestrTableModel.h \
    policestation/PoliceStationItemDelegate.h \
    policestation/PoliceStationModel.h \
    model/AbstractModel.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
