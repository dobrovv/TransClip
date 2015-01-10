#include "TCDefDictWidget.h"
#include <QHeaderView>


TCDefDictWidget::TCDefDictWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setColumnCount(2);
    setHeaderHidden(true);
    setAnimated(true);
    setIndentation(15);
    setRootIsDecorated(true);

    setWordWrap(true);
    //setUniformRowHeights(true);

    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void TCDefDictWidget::setDictData(const GTApiTranslation & gtApiTr)
{
    QTreeWidget::clear();
    int index = 0;

    const QList<GTDefDict>& defDicts = gtApiTr.getDefDictionary();

    foreach ( const GTDefDict& dict, defDicts ) {
        QTreeWidgetItem *defDictItem = new TCDefDictItem(dict);
        insertTopLevelItem(index++, defDictItem);
    }
}
