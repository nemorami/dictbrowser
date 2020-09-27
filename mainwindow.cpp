#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"

#include <QtWebEngineWidgets/QWebEngineView>
#include <QMessageBox>
#include <QtCore/QStandardPaths>
#include <QtSql/QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->insertWidget(ui->actionsearch, &searchedit);
    mainTab = new QTabWidget(this);
    connect(mainTab, &QTabWidget::currentChanged, this, &MainWindow::on_actionsearch_triggered);
    connect(&searchedit, &QLineEdit::returnPressed, this, &MainWindow::on_actionsearch_triggered);
    setCentralWidget(mainTab);
    readInitFile();
    edit_dict = new EditDict();

}

MainWindow::~MainWindow()
{
    //saveInitFile();
    delete ui;
}

void MainWindow::readInitFile()
{
    //database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/dictionary");
    bool ok = db.open();
    qDebug() << ok;
    QSqlQuery query;
    query.prepare("select count(*) from sqlite_master where name = 'dictionary'");
    query.exec();
    if(query.next()) {
        // dictionary 테이블이 없으면 생성한다.
        if(query.value(0).toInt() == 0) {
            query.prepare("create table dictionary(name text, url text)");
            query.exec();
            query.prepare("insert into dictionary (name, url) values \
                   (\"oxford\", \"https://www.oxfordlearnersdictionaries.com/definition/english/QUERY\"), \
                   (\"cambridge\", \"https://dictionary.cambridge.org/dictionary/english/QUERY\"), \
                   (\"collins\", \"https://www.collinsdictionary.com/dictionary/english/QUERY\"), \
                   (\"daum\", \"https://dic.daum.net/search.do?q=QUERY\"), \
                   (\"longman\", \"https://www.ldoceonline.com/dictionary/QUERY\"), \
                   (\"merriam\", \"https://www.merriam-webster.com/dictionary/QUERY\"), \
                   (\"naver\", \"https://en.dict.naver.com/#/search?query=QUERY\")");
            query.exec();
        }
    } else {
            qDebug() << "somethin wrong";
    }
    query.prepare("select name, url from dictionary");
    query.exec();

    while(query.next()){
        setDictList(query.value(0).toString(), query.value(1).toString());
    }
}


void MainWindow::setDictList(QString key, QString value)
{
    dictList[key] = value;
    QWebEngineView *view = new QWebEngineView(this);

    mainTab->addTab(view, key);
}

void MainWindow::on_actionsearch_triggered()
{
    QString search = searchedit.text();
    if (!search.isEmpty()) {
        int index = mainTab->currentIndex();

        QString url = dictList[mainTab->tabText(index)];

        url.replace("QUERY", search);
        qDebug() << "search: " << search << Qt::endl <<  "url:" << url << Qt::endl;
        qobject_cast<QWebEngineView *>(mainTab->currentWidget())->load(QUrl(url));
    }
}

void MainWindow::on_actionedit_dict_triggered()
{
    edit_dict->show();
}

