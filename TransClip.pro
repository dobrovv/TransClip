QT += widgets gui network

SOURCES += \
    main.cpp \
    Popup/TCPopupWidget.cpp \
    Popup/TCPopup.cpp \
    Popup/TCPosDictWidget.cpp \
    GoogleTranslateApi/gtapi.cpp \
    GoogleTranslateApi/gtapitranslation.cpp \
    GoogleTranslateApi/gtreplyobject.cpp \


HEADERS += \
    Popup/TCPopupWidget.h \
    Popup/TCPopup.h \
    Popup/TCPosDictWidget.h \
    GoogleTranslateApi/gtapi.h \
    GoogleTranslateApi/gtapitranslation.h \
    GoogleTranslateApi/gtreplyobject.h \

VERSION = 0.1
QMAKE_TARGET_COMPANY = VaSaKed
QMAKE_TARGET_PRODUCT = TransCip
QMAKE_TARGET_DESCRIPTION = TransClip - Online Translator
QMAKE_TARGET_COPYRIGHT =

OTHER_FILES += \
    GoogleTranslateApi/GoogleTranslateFormat.txt
