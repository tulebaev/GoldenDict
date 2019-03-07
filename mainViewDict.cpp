#include <QApplication>
#include <QTextCodec>
#include "viewDict.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QTextCodec* utfCodec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForCStrings(utfCodec);
  ViewDict viewDict;
  viewDict.resize(600, 400);
  viewDict.show();
  return app.exec();
}
