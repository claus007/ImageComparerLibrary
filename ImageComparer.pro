#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T20:57:43
#
#-------------------------------------------------

QT       += core svg

TARGET = ImageComparer
TEMPLATE = lib

#CONFIG = staticlib

DEFINES += IMAGECOMPARER_LIBRARY

SOURCES += ImageComparer.cpp \
    ComparerWidget.cpp

HEADERS += ImageComparer.h\
        imagecomparer_global.h \
    ComparerWidget.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DESTDIR = ../build

FORMS += \
    ComparerWidget.ui
