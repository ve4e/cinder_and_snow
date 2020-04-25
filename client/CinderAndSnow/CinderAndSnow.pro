#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T13:22:18
#
#-------------------------------------------------

QT += core gui multimedia qml quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = CinderAndSnow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += CLIENT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

DESTDIR = ../BUILDING
OBJECTS_DIR = ../BUILDING 

SOURCES += \
    Area.cpp \
    DialogChoiceMap.cpp \
    characters/Asset.cpp \
    characters/CharacterController.cpp \
    characters/CharacterView.cpp \
    game_widgets/UnitInfo.cpp \
    game_widgets/UnitPanel.cpp \
    main.cpp \
    Mainwindow.cpp \
    NetworkManager.cpp \
    NetworkObserver.cpp \
    Screensaver.cpp \
    Tracer.cpp \
    GM.cpp \
    map/Hex.cpp \
    map/HexController.cpp \
    map/HexView.cpp \
    game_widgets/MenuButton.cpp \
    AreaScene.cpp \
    units/Unit.cpp

HEADERS += \
    Area.h \
    Configure.h \
    DialogChoiceMap.h \
    Mainwindow.h \
    NetworkManager.h \
    NetworkObserver.h \
    Screensaver.h \
    Tracer.h \
    MapRW.h \
    GM.h \
    characters/Asset.h \
    characters/Character.h \
    characters/CharacterController.h \
    characters/CharacterView.h \
    game_widgets/UnitInfo.h \
    game_widgets/UnitPanel.h \
    map/EMap.h \
    map/Hex.h \
    map/HexController.h \
    map/HexView.h \
    game_widgets/MenuButton.h \
    AreaScene.h \
    units/Unit.h
FORMS += \
    game_widgets/UnitInfo.ui \
    game_widgets/UnitPanel.ui \
    mainwindow.ui \
    dialogchoicemap.ui

#LIBS += -lboost_system
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=

RESOURCES += \
    res.qrc

DISTFILES += \
    ../python/map_generator.py
