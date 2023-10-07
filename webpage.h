#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>

class WebPage : public QWebEnginePage
{
    Q_OBJECT

    public:
        explicit WebPage(QObject *parent = 0);

    protected:
        bool certificateError(const QWebEngineCertificateError &error);

};

#endif // WEBPAGE_H
