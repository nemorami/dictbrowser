#ifndef EDITDICT_H
#define EDITDICT_H

#include <QAbstractButton>
#include <QDialog>

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
};

#endif // EDITDICT_H
