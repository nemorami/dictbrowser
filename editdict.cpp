#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QStandardItemModel>
#include "editdict.h"
#include "ui_editdict.h"
#include <QPushButton>
#include <QDebug>


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
//        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "nemorami", "dictbrowser");
//        settings.remove("DICTIONARY");
//        settings.beginGroup("DICTIONARY");
//        QAbstractItemModel *model = ui->tableView->model();
//        for (int i = 0; i < model->rowCount(); ++i) {
//            settings.setValue(model->data(model->index(i,0)).toString(), model->data(model->index(i,1)).toString());
//            qDebug() << model->data(model->index(i,0)).toString();
//        }
//        settings.endGroup();
        model.submitAll();
        break;
    }
    case QDialogButtonBox::Apply:
        ui->tableView->model()->insertRow(ui->tableView->model()->rowCount());
        ui->tableView->model()->submit();
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
