QT += core
QT -= gui

CONFIG += c++11

TARGET = data-structure
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    arbitrage.cpp \
    bellman-ford.cpp \
    criticalpath.cpp \
    dominoeffect.cpp \
    kruskal.cpp \
    prim.cpp \
    theuniquemst.cpp \
    windowpains.cpp \
    spfa.cpp \
    slivercowparty.cpp \
    wormholes.cpp \
    floyd.cpp \
    fibernetwork.cpp \
    heavycargo.cpp \
    burnthelinkedcamp.cpp \
    intervals.cpp \
    doorman.cpp \
    playonwords.cpp \
    domino_euler.cpp \
    code.cpp \
    fleury.cpp \
    ford_fullkerson.cpp \
    pigs.cpp \
    drainage_ditches.cpp

HEADERS += \
    common.h
