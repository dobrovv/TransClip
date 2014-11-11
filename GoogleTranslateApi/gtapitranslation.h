#ifndef GTAPITRANSLATION_H
#define GTAPITRANSLATION_H

#include "gtreplyobject.h"

#include <QStringList>

enum GTPosEnum{ NOUN=1,
                VERB=2,
                ADJECTIVE=3,
                CONJUNCTION=7,
                PRONOUN=8,
                PHRASE=10};

struct GTDictPosEntry{
    QString prefixWord;
    QString translation;
    qreal score;
    QStringList reTranslations;
    QStringList synsetIds;
};

struct GTDictPos{
    QString posName;
    GTPosEnum posEnum;
    QString wordBase;
    QList<GTDictPosEntry> entries;
};

class GTApiTranslation
{
    QString rawReply;
    GTReplyObject root;

public:
    GTApiTranslation( const GTReplyObject &);

    QStringList trans() const;
    QStringList orig() const;
    QString translit() const;
    QString srcTranslit() const;
    QString srcLang() const;

    QList<GTDictPos> getPosDictionary() const;

    const GTReplyObject & replyObjectRef() const;
};

#endif // GTAPITRANSLATION_H
