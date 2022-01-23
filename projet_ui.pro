QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entity.cc \
    Fille.cc \
    Fils.cc \
    Histoire.cc \
    Mere.cc \
    Objet.cc \
    Pere.cc \
    Personnage.cc \
    besoin.cpp \
    besoin_expedition.cpp \
    custompixmapitem.cpp \
    main.cpp \
    mainwindow.cpp \
    perso_expedition.cpp

HEADERS += \
    Entity.hh \
    Fille.hh \
    Fils.hh \
    Histoire.hh \
    Mere.hh \
    Objet.hh \
    Pere.hh \
    Personnage.hh \
    besoin.h \
    besoin_expedition.h \
    custompixmapitem.h \
    mainwindow.h \
    perso_expedition.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
