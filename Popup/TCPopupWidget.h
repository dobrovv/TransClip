#ifndef TCPOPUPWIDGET_H
#define TCPOPUPWIDGET_H

#include "TCPopup.h"
#include "TCPosDictWidget.h"
#include "GoogleTranslateApi/gtapi.h"

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
    QLabel *lblLangSelect;
    QPushButton *btnDialogPopup;

    TCPosDictWidget *posDictWgt;

    QString src_lang;
    QString dst_lang;

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
