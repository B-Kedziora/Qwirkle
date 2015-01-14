#-------------------------------------------------
#
# Project created by QtCreator 2014-12-31T16:47:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    startdialog.cpp \
    Commons/piece.cpp \
    Commons/board.cpp \
    boarddisplayer.cpp \
    Commons/connectiondata.cpp \
    Commons/utils.cpp \
    Commons/player.cpp \
    Commons/message.cpp \
    connection.cpp

HEADERS  += widget.h \
    startdialog.h \
    Commons/piece.h \
    Commons/board.h \
    boarddisplayer.h \
    Commons/connectiondata.h \
    Commons/utils.h \
    Commons/player.h \
    Commons/message.h \
    connection.h

FORMS    += widget.ui \
    startdialog.ui

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    Gfx/mail_send.png
