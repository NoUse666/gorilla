#-------------------------------------------------
#
# Project created by QtCreator 2012-11-16T04:15:35
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Gorilla
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    gorilla.cc \
    glwidget.cc \
    building.cc \
    control.cc \
    cameracontrol.cc \
    camera.cc \
    functions.cc \
    banana.cc \
    physiccontrol.cc \
    vao.cc

HEADERS  += mainwindow.hh \
    gorilla.hh \
    glwidget.hh \
    building.hh \
    structs.hh \
    control.hh \
    cameracontrol.hh \
    camera.hh \
    functions.hh \
    banana.hh \
    physiccontrol.hh \
    vao.hh \
    includes.hh

FORMS    += mainwindow.ui

LIBS += -L/usr/local/lib -lGLU -lglut -lGLEW

CFLAGS += -DGL_GLEXT_PROTOTYPES

OTHER_FILES += \
    shader.vsh \
    shader.fsh
