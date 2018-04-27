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
    drainage_ditches.cpp \
    optimal_milking.cpp \
    power_network.cpp \
    dualcorecpu.cpp \
    paratroopters.cpp \
    friendship.cpp \
    min_max_flow_with_behind.cpp \
    reactorcooling.cpp \
    budget.cpp \
    noi2008.cpp \
    matrixtravels.cpp \
    hungarian_method.cpp \
    place_the_roborts.cpp \
    machine_schedule.cpp \
    courses.cpp \
    destroying_the_graph.cpp \
    spf.cpp \
    tarjan.cpp \
    cable_tv_network.cpp \
    burning_bridges.cpp \
    knights_of_the_round_table.cpp

HEADERS += \
    common.h
