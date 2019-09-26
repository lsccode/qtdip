#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T12:28:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtdip
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
        main/main.cpp \
        main/mainwindow.cpp \
    picWidget/playwidget.cpp \
    widgetShow/widgetshow.cpp \
    widgetGrayTransform/widgetgraytransform.cpp \
    widgetGeometry/widgetgeometry.cpp \
    widgetGeometry/dialogMove.cpp \
    widgetGeometry/dialogZoom.cpp \
    widgetGeometry/dialogRotate.cpp \
    widgetGrayTransform/dialogThreshold.cpp \
    widgetGrayTransform/dialogThresholdTwo.cpp \
    widgetGrayTransform/dialogGrayWindow.cpp

HEADERS += \
        main/mainwindow.h \
    picWidget/playwidget.h \
    widgetShow/widgetshow.h \
    widgetGrayTransform/widgetgraytransform.h \
    widgetGeometry/widgetgeometry.h \
    widgetGeometry/dialogMove.h \
    widgetGeometry/dialogZoom.h \
    widgetGeometry/dialogRotate.h \
    widgetGrayTransform/dialogThreshold.h \
    widgetGrayTransform/dialogThresholdTwo.h \
    widgetGrayTransform/dialogGrayWindow.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/qtdip.qrc
