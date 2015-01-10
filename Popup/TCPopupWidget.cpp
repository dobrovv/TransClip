#include "TCPopupWidget.h"

#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QPainter>
#include <QDebug>

TCPopupWidget::TCPopupWidget()
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(255,255,255));
    palette.setColor(QPalette::WindowText, QColor(25, 25, 25));
    setPalette(palette);

    lneInput = new QLineEdit(this);
    connect(lneInput, SIGNAL(returnPressed()),
            this,  SLOT(onInputLineEnterPressed()));

    lblOutput = new QLabel(this);
    lblOutput->setWordWrap(true);
    lblOutput->setAlignment(Qt::AlignTop);
    lblOutput->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, QColor(226, 237, 253));
    QFont font(lblOutput->font());
    font.setPixelSize(font.pointSize()+8);
    lblOutput->setFont(font);
    lblOutput->setPalette(palette);

    langBox = new TCLangBox(this);
    connect(langBox, SIGNAL(sourceLangChanged(QString)), SLOT(onLanguageChanged()));
    connect(langBox, SIGNAL(targetLangChanged(QString)), SLOT(onLanguageChanged()));

    btnDialogPopup = new QPushButton(this);
    btnDialogPopup->setIcon(QIcon("img/pin.ico"));
    btnDialogPopup->setCheckable(true);
    btnDialogPopup->setFixedSize(btnDialogPopup->sizeHint());
    connect(btnDialogPopup, SIGNAL(clicked(bool)),
            SLOT(setStaysOnTop(bool)));

    dictsWgt = new TCTabDictWidget(this);

    QHBoxLayout *topRowLayout = new QHBoxLayout;
    topRowLayout->addWidget(lblOutput);
    topRowLayout->addWidget(btnDialogPopup);
    topRowLayout->setAlignment(btnDialogPopup, Qt::AlignTop);

    QHBoxLayout *midRowLayout = new QHBoxLayout;
    midRowLayout->addWidget(lneInput);
    midRowLayout->addWidget(langBox);
    midRowLayout->setAlignment(langBox, Qt::AlignRight);

    QHBoxLayout *btmRowLayout = new QHBoxLayout;
    btmRowLayout->addWidget(dictsWgt);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topRowLayout);
    mainLayout->addLayout(midRowLayout);
    mainLayout->addLayout(btmRowLayout);
    setLayout(mainLayout);

    gtApi = new GTApi(this);
    connect(gtApi, SIGNAL(translationReady(GTApiTranslation)),
            this,  SLOT(onTranslationReady(GTApiTranslation)));

    connect(QApplication::clipboard(), SIGNAL(changed(QClipboard::Mode)),SLOT(onClipBoardChanged(QClipboard::Mode)));
}

void TCPopupWidget::onClipBoardChanged(QClipboard::Mode)
{
    static quint64 prevPressTime_ms;

    quint64 pressTime_ms = QDateTime::currentMSecsSinceEpoch();
    bool doubleClick = (pressTime_ms - prevPressTime_ms) < 500 ? true : false;
    prevPressTime_ms = pressTime_ms;

    if (!doubleClick)
        return;

    QString copyText = QApplication::clipboard()->text().trimmed();

    lneInput->setText(copyText);
    lblOutput->setText("...");
    gtApi->translate(copyText, langBox->targetLang(), langBox->sourceLang());

    showPopup();

}

void TCPopupWidget::onInputLineEnterPressed()
{
    QString text = lneInput->text();
    gtApi->translate(text, langBox->targetLang(), langBox->sourceLang());
    lblOutput->setText("...");
}

void TCPopupWidget::onLanguageChanged()
{
    onInputLineEnterPressed();
}

void TCPopupWidget::onTranslationReady(const GTApiTranslation &gtApiTr)
{
    if (langBox->sourceLang() == "auto") {
        langBox->setAutoLangName("Auto - " + gtApiTr.detectedSourceLang());
    }

    QString trans = QString("<b>%1</b>").arg(gtApiTr.translation().join(""));
    lblOutput->setText(trans);
    dictsWgt->setDictsData(gtApiTr);
}

void TCPopupWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (popupStaysOnTop())
        return;

    QPainter painter(this);

    QPen pen(Qt::SolidLine);
    pen.setWidth(1);

    if (isActiveWindow()) {
        pen.setColor(palette().color(QPalette::Active, QPalette::Highlight));
    } else {
        painter.setPen(pen); // No stroke
    }

    painter.drawRect(0, 0, width()-1, height()-1);
}
