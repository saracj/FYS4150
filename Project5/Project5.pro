TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

LIBS += -larmadillo -lblas -llapack
