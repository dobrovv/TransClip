#ifndef TCTABDICTWIDGET_H
#define TCTABDICTWIDGET_H

#include <QTabWidget>

#include "TCPosDictWidget.h"
#include "TCDefDictWidget.h"

#include "GoogleTranslateApi/GTApi.h"

class TCTabDictWidget : public QTabWidget
{
    Q_OBJECT

    int posDictIdx;
    int defDictIdx;

    TCPosDictWidget *posDictWgt;
    TCDefDictWidget *defDictWgt;

public:
    explicit TCTabDictWidget(QWidget *parent = 0);
    void setDictsData(const GTApiTranslation &gtApiTr);


signals:

public slots:

};

#endif // TCTABDICTWIDGET_H
