#include <QtGui\QLabel>
#include <QtGui\QLayout>
#include <QtGui\QLineEdit>
#include <QtGui\QListWidget>
#include <QtGui\QTextBrowser>
#include <QtGui\QPushButton>
#include <QtGui\QMessageBox>
#include <stardict.hh>
#include <wstring_qt.hh>
#include "viewDict.h"

ViewDict::ViewDict(QWidget* parent) : QWidget(parent), wordFinder(this)
{
  QVBoxLayout* layout = new QVBoxLayout(this);
  QHBoxLayout* topBar = new QHBoxLayout;
  QLabel* label = new QLabel("Request word:", this);
  topBar->addWidget(label);
  stringRequest = new QLineEdit(this);
  topBar->addWidget(stringRequest);
  QPushButton* searchButton = new QPushButton("Search", this);
  topBar->addWidget(searchButton);
  layout->addLayout(topBar);
  QHBoxLayout* viewPanel = new QHBoxLayout;
  listView = new QListWidget(this);
  viewPanel->addWidget(listView);
  articleView = new QTextBrowser(this);
  articleView->setFocusPolicy(Qt::NoFocus);
  viewPanel->addWidget(articleView);
  viewPanel->setStretchFactor(listView, 1);
  viewPanel->setStretchFactor(articleView, 2);
  layout->addLayout(viewPanel);

  std::vector<std::string> dictNames;
  dictNames.push_back("eng_rus_full.ifo");
  dictionaries = Stardict::makeDictionaries(dictNames, "", *this);

  connect(stringRequest, SIGNAL(returnPressed()), SLOT(submitRequest()));
  connect(searchButton, SIGNAL(clicked()), SLOT(submitRequest()));
  connect(&wordFinder, SIGNAL(finished()), SLOT(wordChanged()));
  connect(listView, SIGNAL(currentRowChanged(int)), SLOT(getOtherArticle(int)));
  searchButton->setDefault(true);
}

void ViewDict::submitRequest() {
  if (stringRequest->text() == "") {
    QMessageBox::warning(this, "Input error", "Please enter a word");
    return;
  }
  wordFinder.prefixMatch(stringRequest->text(), dictionaries);
}

void ViewDict::wordChanged() {
  articleView->clear();
  listView->clear();
  WordFinder::SearchResults const& results = wordFinder.getResults();
  if (results.empty()) return;
  for (size_t k = 0; k < results.size(); ++k)
    listView->addItem(new QListWidgetItem(results[k].first));
  listView->setCurrentRow(0);
  listView->setFocus();
}

void ViewDict::getOtherArticle(int row) {
  if (row == -1) return;
  gd::wstring word = gd::toWString(listView->item(row)->text().trimmed());
  std::vector<gd::wstring> alts;
  sptr<Dictionary::DataRequest> request = dictionaries.front()->getArticle(word, alts);
  connect(request.get(), SIGNAL(finished()), this, SLOT(showArticle()));
  dictRequests.push_back(request);
}

void ViewDict::showArticle() {
  QString article =
    "<html>"
    "<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head>"
    "<body>";
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
  articleView->setHtml(article);
}
