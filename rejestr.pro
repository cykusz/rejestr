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
    model/AbstractModel.cpp \
    staff/StaffModel.cpp \
    staff/StaffItemDelegate.cpp \
    core/model/ModelObserver.cpp \
    widgets/ScrollTableWidget.cpp \
    casein/CaseInModel.cpp \
    model/AbstractListModel.cpp \
    casein/CaseInItemDelegate.cpp \
    validators/NotEmptyValidator.cpp \
    model/AbstractScrollableModel.cpp

HEADERS  += MainWindow.h \
    core/sql/SqlConnectionObserver.h \
    SqlConnectionController.h \
    data/DataStructure.h \
    widgets/RejestrTableView.h \
    model/ModelInterface.h \
    model/RejestrTableModel.h \
    policestation/PoliceStationItemDelegate.h \
    policestation/PoliceStationModel.h \
    model/AbstractModel.h \
    staff/StaffModel.h \
    staff/StaffItemDelegate.h \
    core/model/ModelObserver.h \
    widgets/ScrollTableWidget.h \
    casein/CaseInModel.h \
    model/AbstractListModel.h \
    casein/CaseInItemDelegate.h \
    validators/NotEmptyValidator.h \
    model/AbstractScrollableModel.h

FORMS    += MainWindow.ui \
    widgets/ScrollTableWidget.ui

RESOURCES += \
    resources.qrc
