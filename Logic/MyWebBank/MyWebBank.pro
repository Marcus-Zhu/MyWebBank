#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T16:05:39
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       -= gui

TARGET = MyWebBank
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    WebBankCurrentUser.cpp \
    WebBankDataBaseManip.cpp \
    WebBankUser.cpp \
    WebBankTransfer.cpp \
    WebBankPayment.cpp \
    WebBankCreditCard.cpp \
    WebBankQuery.cpp \
    WebBankSystemMessage.cpp \
    WebBankAccount.cpp \




HEADERS += \
    WebBankCurrentUser.h \
    WebBankDataBaseManip.h \
    WebBankUser.h \
    WebBankTransfer.h\
    WebBankPayment.h \
    WebBankCreditCard.h \
    WebBankQuery.h \
    WebBankSystemMessage.h \
    WebBankAccount.h\


