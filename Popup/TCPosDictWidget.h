#ifndef TCPOSDICTWIDGET_H
#define TCPOSDICTWIDGET_H

#include "GoogleTranslateApi/gtapi.h"
#include <QTreeWidget>

class TCPosDictWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TCPosDictWidget(QWidget *parent = 0);

signals:

public slots:
    void setPosDictionary(const QList<GTDictPos>& posDicts);

};

#endif // TCPOSDICTWIDGET_H
