//
// Created by nemorami on 22. 11. 29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchedList.h" resolved

#include "searchedlist.h"
#include "ui_searchedlist.h"


SearchedList::SearchedList(QWidget *parent) :
        QWidget(parent), ui(new Ui::SearchedList) {
    ui->setupUi(this);
}

SearchedList::~SearchedList() {
    delete ui;
}
