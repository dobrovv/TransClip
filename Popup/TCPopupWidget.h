#ifndef TCPOPUPWIDGET_H
#define TCPOPUPWIDGET_H

#include "TCPopup.h"
#include "TCLangBox.h"
#include "TCPosDictWidget.h"
#include "GoogleTranslateApi/GTApi.h"

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class TCPopupWidget : public QWidget
{
    Q_OBJECT

    TCPopup *popup;
    QLineEdit *lneInput;
    QLabel *lblOutput;
    TCLangBox *langBox;
    QPushButton *btnDialogPopup;

    TCPosDictWidget *posDictWgt;

public:
    explicit TCPopupWidget(TCPopup *parent);

signals:

public slots:

private slots:
    void onClipBoardChanged(QClipboard::Mode mode);
    void onInputLineEnterPressed();
    void onTranslationReady(const GTApiTranslation& gtApiTr);

private:
    void paintEvent(QPaintEvent *event);

private:
    GTApi   *gtApi;
};

#endif // TCPOPUPWIDGET_H
