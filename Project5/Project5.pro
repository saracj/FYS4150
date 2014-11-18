TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    particles.cpp \
    jump.cpp

LIBS += -larmadillo -lblas -llapack

HEADERS += \
    particles.h \
    jump.h
