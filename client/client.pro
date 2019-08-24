#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T19:55:32
#
#-------------------------------------------------

QT       += core gui network sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    chat.cpp \
    add.cpp \
    del.cpp \
    alter.cpp

HEADERS  += widget.h \
    chat.h \
    add.h \
    del.h \
    alter.h

FORMS    += widget.ui \
    chat.ui \
    add.ui \
    del.ui \
    alter.ui
