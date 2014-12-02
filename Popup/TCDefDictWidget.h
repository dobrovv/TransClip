#ifndef TCDEFDICTWIDGET_H
#define TCDEFDICTWIDGET_H

#include <QTreeWidget>

class TCDefDictWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TCDefDictWidget(QWidget *parent = 0);

signals:

public slots:

};

#endif // TCDEFDICTWIDGET_H

//struct TCDefDictItem : public QTreeWidgetItem{

//    TCDefDictItem(const GTDefDict& dict) {
//        int index = 0;

//        foreach (const GTDefDictEntry & entry, dict.entries) {
//            QTreeWidgetItem * entryDef = new QTreeWidgetItem(QStringList(entry.definition));
//            if (entry.definitionExampleUsage.size()) {
//                QTreeWidgetItem *entryDefExample = new QTreeWidgetItem(QStringList(entry.definitionExampleUsage));
//                entryDef->addChild(entryDefExample);
//            }
//            addChild(entryDef);
//        }
//        setText(0, dict.posName);
//    }
//};


//class TCDefDictWidget : public QTreeWidget{

//    Q_OBJECT

//public:
//    explicit TCDefDictWidget(QWidget *parent = 0) :
//        QTreeWidget(parent)
//    {
//        setColumnCount(2);
//        setHeaderHidden(true);
//        setAnimated(true);
//        setIndentation(15);
//        setRootIsDecorated(true);

//        setWordWrap(true);
//        //setUniformRowHeights(true);

//        header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
//        header()->setSectionResizeMode(1, QHeaderView::Stretch);
//    }

//signals:

//public slots:
//    void setDefDictionary(const QList<GTDefDict>& defDicts){
//        QTreeWidget::clear();
//        int index = 0;
//        foreach ( const GTDefDict& dict, defDicts ) {
//            QTreeWidgetItem *defDictItem = new TCDefDictItem(dict);
//            insertTopLevelItem(index++, defDictItem);
//        }
//    }

//};
