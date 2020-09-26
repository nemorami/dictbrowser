#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"

#include <QtWebEngineWidgets/QWebEngineView>
#include <QMessageBox>




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
    edit_dict = new EditDict();
    readInitFile();

}

MainWindow::~MainWindow()
{
    //saveInitFile();
    delete ui;
}

void MainWindow::readInitFile()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "nemorami", "dictbrowser");

    settings.beginGroup("DICTIONARY");
    QStringList keys = settings.allKeys();
    if (keys.empty()) {
         settings.setValue("oxford", "https://www.oxfordlearnersdictionaries.com/definition/english/QUERY");
         settings.setValue("cambridge", "https://dictionary.cambridge.org/dictionary/english/QUERY");
         settings.setValue("collins", "https://www.collinsdictionary.com/dictionary/english/QUERY");
         settings.setValue("daum", "https://dic.daum.net/search.do?q=QUERY");
         settings.setValue("longman", "https://www.ldoceonline.com/dictionary/QUERY");
         settings.setValue("merriam", "https://www.merriam-webster.com/dictionary/QUERY");
         settings.setValue("naver", "https://en.dict.naver.com/#/search?query=QUERY");
    }

    for (auto key : keys) {
        setDictList(key, settings.value(key).toString());

    }
    settings.endGroup();

}

void MainWindow::saveInitFile()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "nemorami", "dictbrowser");
    settings.setValue("DICTIONARY/oxford", "https://www.oxfordlearnersdictionaries.com/definition/english/QUERY");
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
        QWebEngineView *widget = qobject_cast<QWebEngineView *>(mainTab->currentWidget());
        QString url = dictList[mainTab->tabText(index)];

        url.replace("QUERY", search);
        qDebug() << "search: " << search << Qt::endl <<  "url:" << url << Qt::endl;
        widget->load(QUrl(url));
    }
}

void MainWindow::on_actionedit_dict_triggered()
{
    edit_dict->show();
}

