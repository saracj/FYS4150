TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    solarsystem.cpp \
    celestialbodies.cpp

HEADERS += \
    solarsystem.h \
    celestialbodies.h


LIBS += -larmadillo -lblas -llapack
