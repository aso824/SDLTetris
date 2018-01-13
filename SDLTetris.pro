TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/utils.cpp \
    src/Config/config.cpp \
    src/Config/readexception.cpp \
    src/Logger/logger.cpp

CONFIG += c++11

LIBS += -lSDL2
LIBS += -lSDL2_image

HEADERS += \
    include/utils.h \
    include/Config/config.h \
    include/Config/readexception.h \
    include/Logger/logger.h \
    include/Logger/loglevel.h \
    include/globals.h
