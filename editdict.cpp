#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QStandardItemModel>
#include "editdict.h"
#include "ui_editdict.h"
#include <QPushButton>
#include <QDebug>
#include <QSqlRecord>
#include <QtSql/QSqlQuery>

EditDict::EditDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDict)
{
    ui->setupUi(this);

    model.setTable("dictionary");
    model.select();
    //QStandardItemModel *model = new QStandardItemModel(0,2);

    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("&Add");
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText("&Delete");
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &EditDict::customMenuRequested);
    // row순서가 변경되면 orderChanged를 true로 설정
    orderChanged = false;
    connect(ui->tableView->verticalHeader(), &QHeaderView::sectionMoved, [=, this](){orderChanged = true;});
//    model.setHeaderData(0, Qt::Horizontal, "이름");
//    model.setHeaderData(1, Qt::Horizontal, "URL");

   /* settings.beginGroup("DICTIONARY");
    size_t idx = 0;
    for (auto key : settings.allKeys()) {
        model->appendRow(new QStandardItem());
        model->setData(model->index(idx, 0), key);
        model->setData(model->index(idx, 1), settings.value(key).toString());
        idx++;
      

    }
    settings.endGroup();
*/
    ui->tableView->setModel(&model);
    ui->tableView->resizeColumnsToContents();
    //세로 헤더를 드래그해서 옮길수 있게 함
    ui->tableView->verticalHeader()->setSectionsMovable(true);



}

EditDict::~EditDict()
{
    delete ui;
}

void EditDict::on_buttonBox_clicked(QAbstractButton *button)
{

    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save: {
        // 순서가 변경되었으면 테이블 내용을 지우고 다시 삽입
        if (orderChanged) {
            QSqlQuery query;
            QSqlDatabase::database().transaction();
            query.exec("delete from dictionary");

            for (int i = 0; i < model.rowCount(); ++i) {
                auto record = model.record(ui->tableView->verticalHeader()->logicalIndex(i));
                qDebug() << record.value(0) << "  " << record.value(1);
                query.prepare("insert into dictionary(name, url) values (:name, :url)");
                query.bindValue(":name", record.value(0));
                query.bindValue(":url", record.value(1));
                query.exec();
            }
            QSqlDatabase::database().commit();
            model.select();
            orderChanged = false;
        }

        break;
    }
    case QDialogButtonBox::Apply:
        model.insertRow(ui->tableView->model()->rowCount());
        model.submit();
        break;

    case QDialogButtonBox::Discard: {

        for (auto row : ui->tableView->selectionModel()->selectedRows()) {
            model.removeRow(row.row());
        }
        model.submit();
        break;
    }
    case QDialogButtonBox::Close:
        close();
        break;
    default:
        break;
    }

}

void EditDict::customMenuRequested(QPoint pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Action1", this));
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

}
