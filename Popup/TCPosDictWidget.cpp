#include "TCPosDictWidget.h"
#include <QHeaderView>

struct TCPosDictEntryItem : public QTreeWidgetItem{
    TCPosDictEntryItem(const GTPosDictEntry& entry){

        QString trans = entry.wordTarget;
        if ( trans.size() > 12 ) {
            trans.insert(trans.size()/2, "-\n ");
        }

        setText(0, trans);
        setText(1, entry.wordRetranslations.join(", "));

        setTextColor(1, QColor("#777"));
    }
};

struct TCPosDictItem : public QTreeWidgetItem{

    TCPosDictItem(const GTPosDict& dict){

        int index = 0;
        QStringList entriesWord;
        foreach (const GTPosDictEntry & entry, dict.entries) {
            TCPosDictEntryItem *entrieItem = new TCPosDictEntryItem(entry);
            insertChild(index++, entrieItem);
            entriesWord << entry.wordTarget;
        }
        setText(0, dict.posNameHl);
        setText(1, entriesWord.join(", "));

        QFont font;
        font.setItalic(true);
        setFont(0, font);
        setTextColor(0, QColor("#777"));
    }
};



TCPosDictWidget::TCPosDictWidget(QWidget *parent) :
    QTreeWidget(parent)
{

    setColumnCount(2);
    setHeaderHidden(true);
    setAnimated(true);
    setIndentation(15);
    setRootIsDecorated(false);

    setWordWrap(true);
    //setUniformRowHeights(true);

    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void TCPosDictWidget::setPosDictionary(const QList<GTPosDict> &posDicts)
{
    QTreeWidget::clear();
    int index =0;

    foreach ( const GTPosDict& dict, posDicts ) {
        TCPosDictItem *posDictItem = new TCPosDictItem(dict);
        insertTopLevelItem(index++, posDictItem);
    }
}
