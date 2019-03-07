TEMPLATE = app
TARGET = testDict
CONFIG += console

QT += xml
DESTDIR = ./
INCLUDEPATH += ./src
QMAKE_LIBDIR += ./
LIBS += -lGoldenDict
LIBS += -lz
win32: LIBS += -lwsock32

HEADERS = testDict.h

SOURCES = mainTestDict.cpp testDict.cpp
