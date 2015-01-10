#include <QApplication>
#include <QIcon>

#include "Popup/TCPopupWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TCPopupWidget popup;

    popup.showPopup();
    popup.hidePopup();

    return app.exec();
}
