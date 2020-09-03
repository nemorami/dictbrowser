#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSettings>
#include <iostream>

#include "editdict.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readInitFile();
    void saveInitFile();
    void setDictList(QString key, QString value);
private slots:
    void on_actionsearch_triggered();
    void on_actionedit_dict_triggered();

private:
    Ui::MainWindow *ui;
    QLineEdit searchedit;
    QHash<QString, QString> dictList;
    QTabWidget *mainTab;
    EditDict *edit_dict;

};
#endif // MAINWINDOW_H
