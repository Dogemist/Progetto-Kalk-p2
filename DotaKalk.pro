#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T14:05:24
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = DotaKalk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    GUI/addwindow.cpp \
    GUI/addwindowh.cpp \
    GUI/addwindows.cpp \
    GUI/addwindowsum.cpp \
    GUI/basewindow.cpp \
    GUI/changewindow.cpp \
    GUI/deletewindow.cpp \
    GUI/herowindow.cpp \
    GUI/skillwindow.cpp \
    GUI/summonedwindow.cpp \
    GUI/timewindow.cpp \
    SOURCE/c++/baseattack.cpp \
    SOURCE/c++/damage.cpp \
    SOURCE/c++/hero.cpp \
    SOURCE/c++/main.cpp \
    SOURCE/c++/mdamage.cpp \
    SOURCE/c++/pdamage.cpp \
    SOURCE/c++/skill.cpp \
    SOURCE/c++/summonedunit.cpp

HEADERS += \
    GUI/addwindow.h \
    GUI/addwindowh.h \
    GUI/addwindows.h \
    GUI/addwindowsum.h \
    GUI/basewindow.h \
    GUI/changewindow.h \
    GUI/deletewindow.h \
    GUI/herowindow.h \
    GUI/skillwindow.h \
    GUI/summonedwindow.h \
    GUI/timewindow.h \
    SOURCE/c++/baseattack.h \
    SOURCE/c++/damage.h \
    SOURCE/c++/hero.h \
    SOURCE/c++/mdamage.h \
    SOURCE/c++/pdamage.h \
    SOURCE/c++/skill.h \
    SOURCE/c++/summonedunit.h

FORMS += \
    GUI/addwindowh.ui \
    GUI/herowindow.ui \
    GUI/summonedwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
