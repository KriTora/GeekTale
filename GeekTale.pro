TEMPLATE    = app
QT          = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    window.cpp

FORMS += \
    window.ui

HEADERS += \
    window.h
