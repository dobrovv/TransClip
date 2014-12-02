#include <QApplication>
#include <QIcon>

#include "Popup/TCPopupWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TCPopup popup;
    TCPopupWidget popupwgt (&popup);

    popup.showPopup();
    popup.hidePopup();

    return app.exec();
}


/*TCLangSelector
    source_lang
    target_lang
    save
    getSourceLang
    getTargetLang
languagesChanged(source_lang, target_lang) */
