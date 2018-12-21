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

TARGET = CG2018
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
    shapes/circle.cpp \
    shapes/oval.cpp \
    shapes/curve.cpp \
    shapes/rectangle.cpp \
    shapes/polygon.cpp \
    common/box.cpp \
    common/common.cpp \
    drawer/linegenerator.cpp \
    drawer/circlegenerator.cpp \
    drawer/ovalgenerator.cpp \
    drawer/curvegenerator.cpp \
    drawer/polygenerator.cpp \
    drawer/rectgenerator.cpp \
    editor/lineeditor.cpp \
    editor/circleeditor.cpp \
    editor/ovaleditor.cpp \
    editor/curveeditor.cpp \
    editor/recteditor.cpp \
    editor/polyeditor.cpp \
    common/cutbox.cpp


HEADERS += \
        ui/mainwindow.h \
    ui/paintwidget.h \
    ui/toolbar.h \
    shapes/shape.h \
    shapes/point.h \
    shapes/line.h \
    shapes/circle.h \
    shapes/oval.h \
    shapes/curve.h \
    shapes/rectangle.h \
    shapes/polygon.h \
    common/common.h \
    common/box.h \
    drawer/drawer.h \
    drawer/linegenerator.h \
    drawer/circlegenerator.h \
    drawer/ovalgenerator.h \
    drawer/curvegenerator.h \
    drawer/polygenerator.h \
    drawer/rectgenerator.h \
    editor/editor.h \
    editor/lineeditor.h \
    common/mode.h \
    editor/circleeditor.h \
    editor/ovaleditor.h \
    editor/curveeditor.h \
    editor/recteditor.h \
    editor/polyeditor.h \
    common/cutbox.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
