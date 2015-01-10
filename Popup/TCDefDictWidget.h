#ifndef TCDEFDICTWIDGET_H
#define TCDEFDICTWIDGET_H

#include <QTreeWidget>
#include <GoogleTranslateApi/GTApi.h>

struct TCDefDictItem : public QTreeWidgetItem{

    TCDefDictItem(const GTDefDict& dict) {
        int index = 0;

        foreach (const GTDefDictEntry & entry, dict.entries) {
            QTreeWidgetItem * entryDef = new QTreeWidgetItem(QStringList(entry.definition));
            if (entry.definitionExampleUsage.size()) {
                QTreeWidgetItem *entryDefExample = new QTreeWidgetItem(QStringList(entry.definitionExampleUsage));
                entryDef->addChild(entryDefExample);
            }
            addChild(entryDef);
        }
        setText(0, dict.posName);
    }
};


class TCDefDictWidget : public QTreeWidget{

    Q_OBJECT

public:
    explicit TCDefDictWidget(QWidget *parent = 0);

signals:

public slots:
    void setDictData(const GTApiTranslation & gtApiTr);

};

#endif // TCDEFDICTWIDGET_H
