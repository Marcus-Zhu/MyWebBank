#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T14:16:41
#
#-------------------------------------------------

QT       += core gui
QT       += sql axcontainer printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBank
TEMPLATE = app

RC_FILE = icon.rc

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
    wmsgbox.cpp \
    wuser.cpp \
    wtransfer.cpp \
    wsysmsg.cpp \
    wquery.cpp \
    wpayment.cpp \
    wDBmanip.cpp \
    waccount.cpp \
    wcreditcard.cpp \
    wcurrentuser.cpp \
    pages2.cpp \
    qcustomplot.cpp

HEADERS  += bankui.h \
    wstackedwidget.h \
    pages.h \
    bars.h \
    wdelegate.h \
    wlogin.h \
    wloading.h \
    wlineedit.h \
    wuimanip.h \
    wmsgbox.h \
    wuser.h \
    wtransfer.h \
    wsysmsg.h \
    wquery.h \
    wpayment.h \
    wDBmanip.h \
    waccount.h \
    wcreditcard.h \
    wcurrentuser.h \
    qcustomplot.h \
    wnetworkcurrency.h

RESOURCES += \
    styleset.qrc

TRANSLATIONS += chn.ts\
    eng.ts\
