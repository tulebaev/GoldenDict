#include <QCoreApplication>
#include <stardict.hh>
#include <wstring_qt.hh>
#include "testDict.h"

TestDict::TestDict(char* stringRequest, QObject* parent) : QObject(parent), wordFinder(this)
{
  std::vector<std::string> dictNames;
  dictNames.push_back("eng_rus_full.ifo");
  dictionaries = Stardict::makeDictionaries(dictNames, "", *this);
  connect(&wordFinder, SIGNAL(finished()), SLOT(wordChanged()));

  wordFinder.prefixMatch(stringRequest, dictionaries);
}

void TestDict::wordChanged() {
  WordFinder::SearchResults const& results = wordFinder.getResults();
  if (results.empty()) return;
#if 0
for (size_t k = 0; k < results.size(); ++k)
  std::cout << results[k].first.toLatin1().data() << std::endl;
std::cout << std::endl;
#endif
  gd::wstring word = gd::toWString(results[0].first.trimmed());
  std::vector<gd::wstring> alts;
  sptr<Dictionary::DataRequest> request = dictionaries.front()->getArticle(word, alts);
  connect(request.get(), SIGNAL(finished()), this, SLOT(showArticle()));
  dictRequests.push_back(request);
}

void TestDict::showArticle() {
  QString article =
    "<html><head>"
    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">"
    "<link rel=\"stylesheet\" href=\"article-style.css\" type=\"text/css\" />"
    "</head><body>";
  while (dictRequests.size()) {
    Dictionary::DataRequest& request = *dictRequests.front();
    //QString errorString = request.getErrorString();
    if (request.dataSize() > 0) {
      std::vector<char>& data = request.getFullData();
      article += QByteArray(&data.front(), data.size());
    }
    dictRequests.pop_front();
  }
  article += "</body></html>";
  std::cout << article.toUtf8().constData() << std::endl;

  QCoreApplication::quit();
}
