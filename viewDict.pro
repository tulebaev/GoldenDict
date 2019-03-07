TEMPLATE = app
TARGET = viewDict

CONFIG += release
QT += xml
DESTDIR = ./
INCLUDEPATH += ./src
#LIBS += -lz
win32: LIBS += -lwsock32 -lzlib

HEADERS = viewDict.h \
  src/dictionary.hh \
  src/wordfinder.hh

SOURCES = mainViewDict.cpp viewDict.cpp \
  src/atomic_rename.cc \
  src/btreeidx.cc \
  src/chunkedstorage.cc \
  src/dictzip.c \
  src/dictionary.cc \
  src/file.cc \
  src/folding.cc \
  src/fsencoding.cc \
  src/htmlescape.cc \
  src/langcoder.cc \
  src/mutex.cc \
  src/stardict.cc \
  src/utf8.cc \
  src/wordfinder.cc \
  src/wstring_qt.cc \
  src/xdxf2html.cc
