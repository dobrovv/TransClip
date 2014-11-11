#include "gtapitranslation.h"

#include <QDebug>

GTApiTranslation::GTApiTranslation(const GTReplyObject & gtReplyObject)
    : root(gtReplyObject)
{

}

QStringList GTApiTranslation::trans() const
{
    QStringList res;    

    foreach( const GTReplyObject &sentence, root[0] ){
        res << sentence[0].toString();
    }

    if (!res.isEmpty())
        res.removeLast();

    return res;
}

QStringList GTApiTranslation::orig() const
{
    QStringList res;
    foreach( const GTReplyObject &sentence, root[0] )
        res << sentence[1].toString();

    if (!res.isEmpty())
        res.removeLast();

    return res;
}

QString GTApiTranslation::translit() const
{
    return root[0][ root[0].size()-1 ][2].toString();
}

QString GTApiTranslation::srcTranslit() const
{
    return root[0][ root[0].size()-1 ][3].toString();
}

QString GTApiTranslation::srcLang() const
{
    return root[2].toString();
}

QList<GTDictPos> GTApiTranslation::getPosDictionary() const
{
    QList<GTDictPos> res;

    foreach ( const GTReplyObject gtDict, root[1] ) {

        GTDictPos dictPos;
        dictPos.posName  = gtDict[0].toString();
        dictPos.posEnum  = (GTPosEnum)((int)gtDict[4].toNum());
        dictPos.wordBase = gtDict[3].toString();

        foreach (const GTReplyObject gtDictEntry, gtDict[2]) {

            GTDictPosEntry dictPosEntry;
            dictPosEntry.translation = gtDictEntry[0].toString();
            dictPosEntry.reTranslations = gtDictEntry[1].toStringList();
            dictPosEntry.synsetIds = gtDictEntry[2].toStringList();
            dictPosEntry.score = gtDictEntry[3].toNum();
            dictPosEntry.prefixWord = gtDictEntry[4].toString();

            dictPos.entries.append(dictPosEntry);
        }

        res.append(dictPos);
    }
    return res;
}

const GTReplyObject & GTApiTranslation::replyObjectRef() const
{
    return root;
}
