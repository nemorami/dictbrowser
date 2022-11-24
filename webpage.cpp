#include "webpage.h"
#include <QWebEngineCertificateError>



bool WebPage::certificateError(const QWebEngineCertificateError &error)
{
    qDebug() << "error: " << error.errorDescription();
    //
    //error.ignoreCertificateError();
    return true; // error.isOverridable();
}

WebPage::WebPage(QWidget *parent) : QWebEnginePage(parent){

}
