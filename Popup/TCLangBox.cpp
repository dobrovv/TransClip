#include "TCLangBox.h"
#include "GoogleTranslateApi/GTLangCode.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QAbstractItemView>

TCLangBox::TCLangBox(QWidget *parent) :
    QWidget(parent)
{   
    sourceLang_m   = "auto";
    targetLang_m   = "en";
    autoLangName_m = GTLangCode::langName("auto");

    cbxSource = new QComboBox(this);
    connect(cbxSource, SIGNAL(currentIndexChanged(int)), SLOT(sourceIndexChanged(int)));
    cbxSource->setInsertPolicy(QComboBox::NoInsert);
    //cbxSource->setEditable(true);
    cbxSource->view()->setTextElideMode(Qt::ElideNone);
    cbxSource->setMaximumWidth(75);

    cbxTarget = new QComboBox(this);
    connect(cbxTarget, SIGNAL(currentIndexChanged(int)), SLOT(targetIndexChanged(int)));
    cbxTarget->setInsertPolicy(QComboBox::NoInsert);
    //cbxTarget->setEditable(true);
    cbxTarget->view()->setTextElideMode(Qt::ElideNone);
    cbxTarget->setMaximumWidth(75);

    updateSourceCombo();
    updateTargetCombo();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(cbxSource);
    layout->addWidget(cbxTarget);
    setLayout(layout);
}

void TCLangBox::setSourceLang(const QString &sourceLang)
{
    if (sourceLang != "auto") {
        sourceLangsStack.removeOne(sourceLang);
        sourceLangsStack.push_front(sourceLang);
    }

    if (sourceLang_m != sourceLang){
        sourceLang_m = sourceLang;
        emit sourceLangChanged(sourceLang);
        qDebug() << "Source Lang Changed:" << sourceLang;
    }

    updateSourceCombo();
}

void TCLangBox::setTargetLang(const QString &targetLang)
{
    if (targetLang != "auto") {
        targetLangsStack.removeOne(targetLang);
        targetLangsStack.push_front(targetLang);
    }

    if (targetLang_m != targetLang){
        targetLang_m = targetLang;
        emit targetLangChanged(targetLang);
        qDebug() << "Target Lang Changed:" << targetLang;
    }

    updateTargetCombo();
}

void TCLangBox::setAutoLangName(const QString &autoLangName)
{
    autoLangName_m = autoLangName;
    updateSourceCombo();
}

void TCLangBox::updateSourceCombo()
{
    disconnect(cbxSource, SIGNAL(currentIndexChanged(int)), this, SLOT(sourceIndexChanged(int)));

    cbxSource->clear();

    foreach (const QString& code, sourceLangsStack)
        cbxSource->addItem(GTLangCode::langName(code), code);

    if (!sourceLangsStack.isEmpty())
        cbxSource->insertSeparator(cbxSource->count());

    cbxSource->addItem(autoLangName_m, "auto");
    cbxSource->insertSeparator(cbxSource->count());

    foreach (const QString& code, GTLangCode::langMap().keys()) {
        if (code != "auto")
            cbxSource->addItem(GTLangCode::langName(code), code);
    }

    int newCurrentIndex = cbxSource->findData(sourceLang_m);
    if (newCurrentIndex != -1)
        cbxSource->setCurrentIndex(newCurrentIndex);

    connect(cbxSource, SIGNAL(currentIndexChanged(int)), SLOT(sourceIndexChanged(int)));
}

void TCLangBox::updateTargetCombo()
{
    disconnect(cbxTarget, SIGNAL(currentIndexChanged(int)), this, SLOT(targetIndexChanged(int)));

    cbxTarget->clear();

    foreach (const QString& code, targetLangsStack)
        cbxTarget->addItem(GTLangCode::langName(code), code);

    if (!targetLangsStack.isEmpty())
        cbxTarget->insertSeparator(cbxTarget->count());

    foreach (const QString& code, GTLangCode::langMap().keys()) {
        if (code != "auto")
            cbxTarget->addItem(GTLangCode::langName(code), code);
    }

    int newCurrentIndex = cbxTarget->findData(targetLang_m);
    if (newCurrentIndex != -1)
        cbxTarget->setCurrentIndex(newCurrentIndex);

    connect(cbxTarget, SIGNAL(currentIndexChanged(int)), SLOT(targetIndexChanged(int)));
}

void TCLangBox::sourceIndexChanged(int index)
{
    QString sourceLang = cbxSource->itemData(index).toString();
    setSourceLang(sourceLang);
}

void TCLangBox::targetIndexChanged(int index)
{
    QString targetLang = cbxTarget->itemData(index).toString();
    setTargetLang(targetLang);
}


