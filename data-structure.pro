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
    windowpains.cpp
