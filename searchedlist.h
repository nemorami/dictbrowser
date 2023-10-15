//
// Created by nemorami on 22. 11. 29.
//

#ifndef DICTBROWSER_SEARCHEDLIST_H
#define DICTBROWSER_SEARCHEDLIST_H

#include <QWidget>
#include <QAbstractButton>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchedList; }
QT_END_NAMESPACE

class SearchedList : public QWidget {
Q_OBJECT

public:
    explicit SearchedList(QWidget *parent = nullptr);

    ~SearchedList() override;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void customMenuRequested(QPoint pos);
    void deleteWord();

private:
    Ui::SearchedList *ui;
    QSqlTableModel model;
};


#endif //DICTBROWSER_SEARCHEDLIST_H
