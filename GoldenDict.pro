TEMPLATE = lib
CONFIG += staticlib release

QT += xml
DESTDIR = ./
INCLUDEPATH += ./src
#LIBS += -lz
win32: {
  INCLUDEPATH += C:/zlib-1.2.8
  LIBS += -lwsock32
}

HEADERS = \
  src/dictionary.hh \
  src/wordfinder.hh

SOURCES = \
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
