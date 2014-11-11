#ifndef GTAPI_H
#define GTAPI_H

#include "gtapitranslation.h"

#include <QObject>

class QNetworkAccessManager;

class GTApi : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *net;

public:
    explicit GTApi(QObject *parent = 0);
    ~GTApi();

signals:
    void translationReady( const GTApiTranslation & gtApiTr );

public slots:
    void translate(const QString& text, const QString& dstLang,
                   const QString& srcLang = "auto", const QString& posLang = "en");
private slots:
    void onReplyFinished();
};

#endif // GTAPI_H
