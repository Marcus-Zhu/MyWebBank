#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T14:16:41
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBank
TEMPLATE = app


SOURCES += main.cpp\
        bankui.cpp \
    wstackedwidget.cpp \
    pages.cpp \
    bars.cpp \
    wdelegate.cpp \
    wlogin.cpp \
    wloading.cpp \
    wlineedit.cpp \
    wuimanip.cpp \
    WebBankCurrentUser.cpp \
    WebBankDataBaseManip.cpp \
    WebBankUser.cpp \
    WebBankSystemMessage.cpp

HEADERS  += bankui.h \
    wstackedwidget.h \
    pages.h \
    bars.h \
    wdelegate.h \
    wlogin.h \
    wloading.h \
    wlineedit.h \
    wuimanip.h \
    WebBankCurrentUser.h \
    WebBankDataBaseManip.h \
    WebBankUser.h \
    WebBankSystemMessage.h

RESOURCES += \
    styleset.qrc

TRANSLATIONS += chn.ts\
    eng.ts\
