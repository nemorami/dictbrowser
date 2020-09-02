#ifndef EDITDICT_H
#define EDITDICT_H

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

private:
    Ui::EditDict *ui;
};

#endif // EDITDICT_H
