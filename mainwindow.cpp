#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "webpage.h"
#include <QtWebEngineWidgets/QWebEngineView>
#include <QMessageBox>
#include <QtCore/QStandardPaths>
#include <QtSql/QSqlQuery>
#include <QDir>

/*clion*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->insertWidget(ui->actionsearch, &searchedit);
    mainTab = new QTabWidget(this);
    connect(mainTab, &QTabWidget::currentChanged, this, &MainWindow::on_actionsearch_triggered);
    connect(&searchedit, &QLineEdit::returnPressed, this, &MainWindow::on_actionsearch_triggered);

    //LineEdit 아래 completer
    completer = new QCompleter(wordList, this);
    searchedit.setCompleter(completer);


    setCentralWidget(mainTab);
    readInitFile();
    readDataFile();

    edit_dict = new EditDict();
    searched_list = new SearchedList();

}

MainWindow::~MainWindow()
{
    //saveInitFile();
    delete ui;
}

void MainWindow::readDataFile()
{
    //database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    // .local/share/dictbrowser
    QString data_dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << data_dir;
    // 데이터 디렉토리가 없으면  생성
    if (!QDir(data_dir).exists())
        QDir().mkdir(data_dir);

    db.setDatabaseName(data_dir + "/dictionary");
    db.open();

    QSqlQuery query;
    //sqlite_master
    query.prepare("select count(*) from sqlite_master where name = 'dictionary'");
    query.exec();
    if(query.next()) {
        // dictionary 테이블이 없으면
        if(query.value(0).toInt() == 0) {
            //테이블을 생성
            query.prepare("create table dictionary(name text, url text)");
            query.exec();
            //초기데이터 적제
            query.prepare("insert into dictionary (name, url) values \
                   (\"oxford\", \"https://www.oxfordlearnersdictionaries.com/definition/english/QUERY\"), \
                   (\"cambridge\", \"https://dictionary.cambridge.org/dictionary/english/QUERY\"), \
                   (\"collins\", \"https://www.collinsdictionary.com/dictionary/english/QUERY\"), \
                   (\"daum\", \"https://dic.daum.net/search.do?q=QUERY\"), \
                   (\"longman\", \"https://www.ldoceonline.com/search/english/direct/?q=QUERY\"), \
                   (\"merriam\", \"https://www.merriam-webster.com/dictionary/QUERY\"), \
                   (\"naver\", \"https://en.dict.naver.com/#/search?query=QUERY\")");
            query.exec();
        }
    } else {
            qDebug() << "something wrong";
    }
    query.prepare("select name, url from dictionary");
    query.exec();

    while(query.next()){
        setDictList(query.value(0).toString(), query.value(1).toString());
        qDebug() << query.value(0).toString() << query.value(1).toString();
    }

    // searched_list 테이블 생성..
    query.prepare("select count(*) from sqlite_master where name = 'searched_list'");
    query.exec();
    // create table if it doesn't exist
    if(query.next()) {
        query.prepare("create table searched_list(word text, date varchar(14))");
        query.exec();
    }
}


void MainWindow::setDictList(QString key, QString value)
{
    dictList[key] = value;
    qDebug() << "key: " << key << Qt::endl;
    QWebEngineView *view = new QWebEngineView(this);
    view->setPage(new WebPage());
    mainTab->addTab(view, key);

}

void MainWindow::on_actionsearch_triggered()
{
    QString search = searchedit.text();
    if (!search.isEmpty()) {
        int index = mainTab->currentIndex();
        qDebug() << "index: " << index << Qt::endl;
        // fixme: 탭 라벨에 &가 추가되어 있음 왜?
        QString url = dictList[(mainTab->tabText(index)).remove("&")];

        url.replace("QUERY", search);
        qDebug() << "search: " << search << Qt::endl <<  "url:" << url << Qt::endl;
        qobject_cast<QWebEngineView *>(mainTab->currentWidget())->setUrl(QUrl(url));
        //view->setPage(new WebPage());

        // insert word in searched list
        // issue: #4
        QSqlQuery query;
        QString now = QDateTime::currentDateTime().toString("yyyyMMdd");
        query.prepare("select * from searched_list where word = :search and date = :now");
        query.bindValue(":search", search);
        query.bindValue(":now", now);
        query.exec();

        if (!query.next()) {
            query.prepare("insert into searched_list values(:search, :now)");
            query.bindValue(":search", search);
            query.bindValue(":now", now);
            query.exec();
            qDebug() << query.executedQuery();
        }
        
    }
}

void MainWindow::on_actionBack_triggered() {
    dynamic_cast<QWebEngineView *>(mainTab->currentWidget())->back();
}

void MainWindow::on_actionedit_dict_triggered()
{
    edit_dict->show();
}

void MainWindow::readInitFile() {
    QSettings settings("nemorami", "dictbrowser");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings("nemorami", "dictbrowser");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QWidget::closeEvent(event);
}

void MainWindow::on_actionForward_griggered() {
    dynamic_cast<QWebEngineView *>(mainTab->currentWidget())->forward();
    

}

void MainWindow::on_actionsearchedList_triggered() {
    searched_list->show();

}

