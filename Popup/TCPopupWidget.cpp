#include "TCPopupWidget.h"

#include <QApplication>
#include <QGridLayout>
#include <QDateTime>
#include <QPainter>
#include <QDebug>

TCPopupWidget::TCPopupWidget(TCPopup *parent) :
    QWidget(parent), popup(parent)

{
    QPalette palette(popup->palette());
    palette.setColor(QPalette::Window, QColor(255,255,255));
    palette.setColor(QPalette::WindowText, QColor(25, 25, 25));
    popup->setPalette(palette);

    lneInput = new QLineEdit(this);
    connect(lneInput, SIGNAL(returnPressed()),
            this,  SLOT(onInputLineEnterPressed()));

    lblOutput = new QLabel(this);
    lblOutput->setWordWrap(true);
    lblOutput->setAlignment(Qt::AlignTop);
    lblOutput->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, QColor(250,250,250));
    QFont font(lblOutput->font());
    font.setPixelSize(font.pointSize()+8);
    lblOutput->setFont(font);
    lblOutput->setPalette(palette);

    langBox = new TCLangBox(this);

    btnDialogPopup = new QPushButton(this);
    btnDialogPopup->setIcon(QIcon("img/pin.ico"));
    btnDialogPopup->setCheckable(true);
    connect(btnDialogPopup, SIGNAL(clicked(bool)),
            popup, SLOT(setStaysOnTop(bool)));

    posDictWgt = new TCPosDictWidget(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(lneInput, 0, 0, 1, 1);
    mainLayout->addWidget(langBox, 0, 1, 1, 1);
    mainLayout->addWidget(btnDialogPopup, 0, 2, 1, 1);
    mainLayout->addWidget(lblOutput, 1, 0, 1, 3);
    mainLayout->addWidget(posDictWgt, 2, 0, 1, 3);
    setLayout(mainLayout);

    gtApi = new GTApi(this);
    connect(gtApi, SIGNAL(translationReady(GTApiTranslation)),
            this,  SLOT(onTranslationReady(GTApiTranslation)));


    connect(QApplication::clipboard(), SIGNAL(changed(QClipboard::Mode)),SLOT(onClipBoardChanged(QClipboard::Mode)));

    popup->setCentralWidget(this);
}

void TCPopupWidget::onClipBoardChanged(QClipboard::Mode)
{
    static quint64 prevPressTime_ms;
    static QString prevCopyText;

    quint64 pressTime_ms = QDateTime::currentMSecsSinceEpoch();
    bool doubleClick = (pressTime_ms - prevPressTime_ms) < 500 ? true : false;
    prevPressTime_ms = pressTime_ms;

    if (!doubleClick)
        return;

    QString copyText = QApplication::clipboard()->text().trimmed();

    //if (copyText != prevCopyText){
        lneInput->setText(copyText);
        lblOutput->setText("...");
        gtApi->translate(copyText, langBox->targetLang(), langBox->sourceLang());
    //}


    popup->showPopup();

    prevCopyText = copyText;
}

void TCPopupWidget::onInputLineEnterPressed()
{
    QString text = lneInput->text();
    gtApi->translate(text, langBox->targetLang(), langBox->sourceLang());
    lblOutput->setText("...");
}

void TCPopupWidget::onTranslationReady(const GTApiTranslation &gtApiTr)
{
    if (langBox->sourceLang() == "auto") {
        //lblLangSelect->setText(QString("%1(%3) - %2").arg(src_lang, dst_lang, gtApiTr.detectedSourceLang()));
    }

    QString trans = QString("<b>%1</b>").arg(gtApiTr.translation().join(""));
    lblOutput->setText(trans);
    posDictWgt->setPosDictionary(gtApiTr.getPosDictionary());
}

void TCPopupWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (popup->popupStaysOnTop())
        return;

    QPainter painter(this);

    QPen pen(Qt::SolidLine);
    pen.setWidth(1);

    if (isActiveWindow()) {
        pen.setColor(palette().color(QPalette::Active, QPalette::Highlight));
    } else {
        painter.setPen(pen); // No stroke
    }

    painter.drawRect(1, 1, width()-2, height()-2);
}
