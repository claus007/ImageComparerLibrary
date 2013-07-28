#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T20:57:43
#
#-------------------------------------------------

QT       += core svg

TARGET = ImageComparer
TEMPLATE = lib

CONFIG += staticlib

DEFINES += IMAGECOMPARER_LIBRARY

SOURCES += ImageComparer.cpp \
    ComparerWidget.cpp \
    threading/ImageProcessorJob.cpp \
    threading/ImageLoaderJob.cpp \
    threading/ImageResizeJob.cpp \
    threading/ImageDiffCalculatorJob.cpp

HEADERS += ImageComparer.h\
        imagecomparer_global.h \
    ComparerWidget.h \
    threading/ImageProcessorJob.h \
    threading/ImageLoaderJob.h \
    threading/ImageResizeJob.h \
    threading/ImageDiffCalculatorJob.h

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

RESOURCES += \
    alternateImages.qrc
