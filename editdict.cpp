#include "editdict.h"
#include "ui_editdict.h"

EditDict::EditDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDict)
{
    ui->setupUi(this);
}

EditDict::~EditDict()
{
    delete ui;
}
