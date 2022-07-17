TEMPLATE    = app
QT          = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    date.cpp \
    main.cpp \
    player.cpp \
    slots.cpp \
    window.cpp

FORMS += \
    window.ui

HEADERS += \
    date.h \
    player.h \
    window.h
