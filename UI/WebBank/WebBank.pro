#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T14:16:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBank
TEMPLATE = app


SOURCES += main.cpp\
        bankui.cpp \
    wstackedwidget.cpp

HEADERS  += bankui.h \
    wstackedwidget.h

RESOURCES += \
    styleset.qrc

TRANSLATIONS += chn.ts\
    eng.ts\
