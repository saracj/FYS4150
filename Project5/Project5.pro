TEMPLATE = app
CONFIG += console
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    particles.cpp \
    jump.cpp

LIBS += -larmadillo -lblas -llapack

HEADERS += \
    particles.h \
    jump.h
