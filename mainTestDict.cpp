#include <QCoreApplication>
#include <QTextCodec>
#include "testDict.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <word>" << std::endl;
    return 1;
  }
  QTextCodec* utfCodec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForCStrings(utfCodec);
  QCoreApplication app(argc, argv);
  TestDict testDict(argv[1]);
  return app.exec();
}
