//
// Created by nemorami on 22. 11. 29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchedList.h" resolved

#include <QMenu>
#include "searchedlist.h"
#include "ui_searchedlist.h"


SearchedList::SearchedList(QWidget *parent) :
        QWidget(parent), ui(new Ui::SearchedList) {
    ui->setupUi(this);
    //check 모델 셋팅을 이 다이얼로그가 열릴때마다 해야하는지?

    model.setTable("searched_list");
    model.select();
    //Check 오른쪽 버튼 눌렀을때 커스텀 메뉴...
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &SearchedList::customMenuRequested);
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

void SearchedList::customMenuRequested(QPoint pos) {
    QModelIndex index = ui->tableView->indexAt(pos);

    QMenu *menu = new QMenu(this);
    QAction *deleteAction = new QAction("&Delete", this);
    menu->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, &SearchedList::deleteWord);
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

}

void SearchedList::deleteWord() {
    // fixme row 전체가 선택되지 안음.. 행 전체를 선택하고 지우면 지워지기는 하는데... 좀 이상함.
    for(auto row : ui->tableView->selectionModel()->selectedRows())
        model.removeRow(row.row());
    model.submit();
}
