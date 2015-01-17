TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../Commons/board.cpp \
    ../Commons/connectiondata.cpp \
    ../Commons/piece.cpp \
    ../Commons/player.cpp \
    ../Commons/utils.cpp \
    qwirkleserver.cpp \
    ../Commons/message.cpp \
    playerhandler.cpp \
    connectionhandler.cpp \
    chat.cpp \
    ../Commons/drop.cpp \
    piecesack.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../Commons/board.h \
    ../Commons/connectiondata.h \
    ../Commons/piece.h \
    ../Commons/player.h \
    ../Commons/utils.h \
    qwirkleserver.h \
    ../Commons/message.h \
    playerhandler.h \
    ConnectionThreadArgs.h \
    connectionhandler.h \
    chat.h \
    ../Commons/drop.h \
    piecesack.h

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

