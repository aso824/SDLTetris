TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/utils.cpp \
    src/Config/config.cpp \
    src/Config/readexception.cpp

CONFIG += c++11

LIBS += -lSDL2
LIBS += -lSDL2_image

HEADERS += \
    include/utils.h \
    include/Config/config.h \
    include/Config/readexception.h
