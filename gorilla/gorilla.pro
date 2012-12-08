#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T04:07:13
#
#-------------------------------------------------

QT       += core gui

TARGET = gorilla
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    vao.cc \
    physiccontrol.cc \
    gorilla.cc \
    glwidget.cc \
    functions.cc \
    control.cc \
    cameracontrol.cc \
    camera.cc \
    building.cc \
    banana.cc

HEADERS  += mainwindow.hh \
    vao.hh \
    structs.hh \
    physiccontrol.hh \
    includes.hh \
    gorilla.hh \
    glwidget.hh \
    functions.hh \
    control.hh \
    cameracontrol.hh \
    camera.hh \
    building.hh \
    banana.hh

FORMS    += mainwindow.ui

OTHER_FILES += \
    shader.vsh \
    shader.fsh \
    Gorilla.pro \
    gorilla.pro.user
