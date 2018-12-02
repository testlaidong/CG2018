#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T17:55:08
#
#-------------------------------------------------

QT       += core gui \
            opengl

LIBS += -lopengl32\
         -lGLU32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicWork
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

INCLUDEPATH += shapes

SOURCES += \
        main.cpp \
        ui/mainwindow.cpp \
    ui/paintwidget.cpp \
    ui/toolbar.cpp \
    shapes/line.cpp \
    shapes/point.cpp \
    common.cpp \
    drawer/linegenerator.cpp \
    shapes/circle.cpp \
    drawer/circlegenerator.cpp \
    shapes/oval.cpp \
    drawer/ovalgenerator.cpp \
    shapes/curve.cpp \
    drawer/curvegenerator.cpp \
    shapes/rectangle.cpp \
    shapes/polygon.cpp \
    drawer/polygenerator.cpp \
    drawer/rectgenerator.cpp \
    box.cpp

HEADERS += \
        ui/mainwindow.h \
    ui/paintwidget.h \
    ui/toolbar.h \
    shapes/shape.h \
    shapes/point.h \
    shapes/line.h \
    common.h \
    drawer/drawer.h \
    drawer/linegenerator.h \
    shapes/circle.h \
    drawer/circlegenerator.h \
    shapes/oval.h \
    drawer/ovalgenerator.h \
    shapes/curve.h \
    drawer/curvegenerator.h \
    shapes/rectangle.h \
    shapes/polygon.h \
    drawer/polygenerator.h \
    drawer/rectgenerator.h \
    box.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
