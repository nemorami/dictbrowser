#include "webpage.h"
#include <QWebEngineCertificateError>



bool WebPage::certificateError(const QWebEngineCertificateError &error)
{
    qDebug() << "error: " << error.description();
    //
    //error.ignoreCertificateError();
    return true; // error.isOverridable();
}

WebPage::WebPage(QObject *parent) : QWebEnginePage(parent){

}
