QT += widgets gui network

SOURCES += \
    main.cpp \
    Popup/TCPopupWidget.cpp \
    Popup/TCPopup.cpp \
    Popup/TCLangBox.cpp \
    Popup/TCPosDictWidget.cpp \
    Popup/TCDefDictWidget.cpp \
    GoogleTranslateApi/GTApi.cpp \
    GoogleTranslateApi/GTApiTranslation.cpp \
    GoogleTranslateApi/GTReplyObject.cpp \
    Popup/TCTabDictWidget.cpp

HEADERS += \
    Popup/TCPopupWidget.h \
    Popup/TCPopup.h \
    Popup/TCLangBox.h \
    Popup/TCPosDictWidget.h \
    Popup/TCDefDictWidget.h \
    GoogleTranslateApi/GTApi.h \
    GoogleTranslateApi/GTApiTranslation.h \
    GoogleTranslateApi/GTReplyObject.h \
    GoogleTranslateApi/GTLangCode.h \
    Popup/TCTabDictWidget.h

VERSION = 0.1
QMAKE_TARGET_COMPANY = VaSaKed
QMAKE_TARGET_PRODUCT = TransCip
QMAKE_TARGET_DESCRIPTION = TransClip - Online Translator
QMAKE_TARGET_COPYRIGHT =

OTHER_FILES += \
    GoogleTranslateApi/GoogleWebTranslateFormat.txt \
    release/icudt51.dll \
    release/icuin51.dll \
    release/icuuc51.dll \
    release/libgcc_s_dw2-1.dll \
    release/libstdc++-6.dll \
    release/libwinpthread-1.dll \
    release/Qt5Core.dll \
    release/Qt5Gui.dll \
    release/Qt5Network.dll \
    release/Qt5Widgets.dll \
    release/TransClip.exe \
    img/screenshot.jpg \
    img/screenshot_small.jpg \
    img/pin.ico
