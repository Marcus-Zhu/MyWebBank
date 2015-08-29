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
    WebBankUser.cpp \
    WebBankAccount.cpp \
    WebBankTransfer.cpp \
    WebBankPayment.cpp \
    WebBankCreditCard.cpp \
    WebBankQuery.cpp \
    WebBankSystemMessage.cpp \
    WebBankDataBaseManip.cpp \
    WebBankCurrentUser.cpp \




HEADERS += \
    WebBankUser.h \
    WebBankAccount.h\
    WebBankTransfer.h\
    WebBankPayment.h \
    WebBankCreditCard.h \
    WebBankQuery.h \
    WebBankSystemMessage.h \
    WebBankDataBaseManip.h \
    WebBankCurrentUser.h \


