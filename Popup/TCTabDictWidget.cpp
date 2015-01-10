#include "TCTabDictWidget.h"

TCTabDictWidget::TCTabDictWidget(QWidget *parent) :
    QTabWidget(parent)
{
    posDictWgt = new TCPosDictWidget(this);
    defDictWgt = new TCDefDictWidget(this);

    setTabPosition(QTabWidget::South);

    posDictIdx = addTab(posDictWgt, "POS");
    defDictIdx = addTab(defDictWgt, "Definition");

}

void TCTabDictWidget::setDictsData(const GTApiTranslation &gtApiTr)
{
    posDictWgt->setDictData(gtApiTr);
    defDictWgt->setDictData(gtApiTr);

    setTabEnabled(posDictIdx, !gtApiTr.getPosDictionary().isEmpty());
    setTabEnabled(defDictIdx, !gtApiTr.getDefDictionary().isEmpty());
}
