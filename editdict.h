#ifndef EDITDICT_H
#define EDITDICT_H

#include <QAbstractButton>
#include <QDialog>
#include <QtSql/QSqlTableModel>
namespace Ui {
class EditDict;
}

class EditDict : public QDialog
{
    Q_OBJECT

public:
    explicit EditDict(QWidget *parent = nullptr);
    ~EditDict();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void customMenuRequested(QPoint pos);

private:
    Ui::EditDict *ui;
    QSqlTableModel model;
    bool orderChanged;
};

#endif // EDITDICT_H
