#include <QApplication>
#include <QIcon>

#include "Popup/TCPopupWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TCPopup popup;
    TCPopupWidget popupwgt (&popup);
    app.setQuitOnLastWindowClosed(false);
    popup.show();
    popup.hide();

    return app.exec();
}
