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
    wstackedwidget.cpp \
    qmenubutton.cpp

HEADERS  += bankui.h \
    wstackedwidget.h \
    qmenubutton.h

RESOURCES += \
    styleset.qrc

TRANSLATIONS += my.ts
