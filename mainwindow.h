#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSettings>
#include <QtSql/QSqlDatabase>
#include <iostream>
#include <QCompleter>

#include "editdict.h"
#include "searchedlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readDataFile();
    void readInitFile();

    void setDictList(QString key, QString value);
public slots:
    void on_actionBack_triggered();

    void on_actionForward_griggered();
    void on_actionsearch_triggered();
    void on_actionedit_dict_triggered();
    void on_actionsearchedList_triggered();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLineEdit searchedit;
    QStringList wordList;
    QCompleter *completer;
    QHash<QString, QString> dictList;
    QTabWidget *mainTab;
    EditDict *edit_dict;
    SearchedList *searched_list;
    QSqlDatabase db;

};
#endif // MAINWINDOW_H
