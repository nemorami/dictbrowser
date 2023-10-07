//
// Created by nemorami on 22. 11. 29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchedList.h" resolved

#include "searchedlist.h"
#include "ui_searchedlist.h"


SearchedList::SearchedList(QWidget *parent) :
        QWidget(parent), ui(new Ui::SearchedList) {
    ui->setupUi(this);
    //check 모델 셋팅을 이 다이얼로그가 열릴때마다 해야하는지?

    model.setTable("searched_list");
    model.select();

    ui->tableView->setModel(&model);
}

SearchedList::~SearchedList() {
    delete ui;
}

void SearchedList::on_buttonBox_clicked(QAbstractButton *button) {

    switch (ui->buttonBox->standardButton(button)) {
        case QDialogButtonBox::Ok :
        case QDialogButtonBox::Cancel:
            close();
            break;
        default:
            break;
    }

}
