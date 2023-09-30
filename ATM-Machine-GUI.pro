QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    database.cpp \
    keypad_4x4.cpp \
    main.cpp \
    mainwindow.cpp \
    pulsebuzzer.cpp \
    pulseled.cpp \
    pushbutton.cpp \
    reservationsystem.cpp \
    scrollingdevice.cpp \
    sevensegmentmodule.cpp \
    transferpage.cpp

HEADERS += \
    Configurations.h \
    account.h \
    database.h \
    keypad_4x4.h \
    mainwindow.h \
    pulsebuzzer.h \
    pulseled.h \
    pushbutton.h \
    reservationsystem.h \
    scrollingdevice.h \
    sevensegmentmodule.h \
    transferpage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
