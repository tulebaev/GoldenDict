#ifndef TESTDICT_H
#define TESTDICT_H

#include <wordfinder.hh>
#include <iostream>

class TestDict : public QObject, Dictionary::Initializing
{
  Q_OBJECT
public:
  TestDict(char* stringRequest, QObject* parent = 0);
  void indexingDictionary(std::string const& dictionaryName) throw() { }
private slots:
  void wordChanged();
  void showArticle();
private:
  WordFinder wordFinder;
  std::vector< sptr<Dictionary::Class> > dictionaries;
  std::list< sptr<Dictionary::DataRequest> > dictRequests;
};

#endif // TESTDICT_H
