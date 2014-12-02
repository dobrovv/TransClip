#ifndef TCLANGBOX_H
#define TCLANGBOX_H

#include <QWidget>

class QComboBox;

class TCLangBox : public QWidget
{
    Q_OBJECT
    QComboBox *cbxSource;
    QComboBox *cbxTarget;

    QList<QString> sourceLangsStack;
    QList<QString> targetLangsStack;

    QString sourceLang_m;
    QString targetLang_m;

public:
    explicit TCLangBox(QWidget *parent = 0);

    inline QString sourceLang() const {return sourceLang_m;}
    inline QString targetLang() const {return targetLang_m;}


signals:
    void sourceLangChanged(const QString& sourceLang);
    void targetLangChanged(const QString& targetLang);

public slots:
    void setSourceLang(const QString& sourceLang);
    void setTargetLang(const QString& targetLang);

private:
    void updateSourceCombo();
    void updateTargetCombo();

private slots:
    void sourceIndexChanged(int index);
    void targetIndexChanged(int index);
};

#endif // TCLANGBOX_H
