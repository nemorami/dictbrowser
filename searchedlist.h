//
// Created by nemorami on 22. 11. 29.
//

#ifndef DICTBROWSER_SEARCHEDLIST_H
#define DICTBROWSER_SEARCHEDLIST_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SearchedList; }
QT_END_NAMESPACE

class SearchedList : public QWidget {
Q_OBJECT

public:
    explicit SearchedList(QWidget *parent = nullptr);

    ~SearchedList() override;

private:
    Ui::SearchedList *ui;
};


#endif //DICTBROWSER_SEARCHEDLIST_H
