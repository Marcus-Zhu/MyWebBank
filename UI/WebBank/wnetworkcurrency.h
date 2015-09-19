#ifndef WNETWORKCURRENCY_H
#define WNETWORKCURRENCY_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

class WNetworkCurrency : public QObject
{
    Q_OBJECT
public:
    static QString getHtml(QString url)
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
        QByteArray responseData;
        QEventLoop eventLoop;
        connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
        eventLoop.exec();       //block until finish
        responseData = reply->readAll();
        return QString(responseData);
    }
};

#endif // WNETWORKCURRENCY_H
