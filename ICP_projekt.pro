#-------------------------------------------------
#
# Project created by QtCreator 2019-04-27T13:26:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP_projekt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    chesswindow.cpp \
    field.cpp \
    figure.cpp \
    board.cpp \
    square.cpp \
    fieldview.cpp \
    controller.cpp \
    boardview.cpp \
    loglist.cpp

HEADERS += \
        mainwindow.h \
    chesswindow.h \
    field.h \
    figure.h \
    board.h \
    square.h \
    fieldview.h \
    controller.h \
    boardview.h \
    loglist.h

FORMS += \
        mainwindow.ui \
    chesswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
