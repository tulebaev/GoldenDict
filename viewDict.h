#ifndef VIEWDICT_H
#define VIEWDICT_H

#include <QtGui\QWidget>
#include "wordfinder.hh"

class QLineEdit;
class QListWidget;
class QListWidgetItem;
class QTextBrowser;

class ViewDict : public QWidget, Dictionary::Initializing
{
  Q_OBJECT
public:
  ViewDict(QWidget* parent = 0);
  void indexingDictionary(std::string const& dictionaryName) throw() { }
private slots:
  void submitRequest();
  void wordChanged();
  void getOtherArticle(int row);
  void showArticle();
private:
  QLineEdit* stringRequest;
  QListWidget* listView;
  QTextBrowser* articleView;
  WordFinder wordFinder;
  std::vector< sptr<Dictionary::Class> > dictionaries;
  std::list< sptr<Dictionary::DataRequest> > dictRequests;
};

#endif // VIEWDICT_H
