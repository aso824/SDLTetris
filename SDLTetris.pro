TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/utils.cpp \
    src/Config/config.cpp \
    src/Config/readexception.cpp \
    src/Logger/logger.cpp \
    src/Config/writeexception.cpp \
    src/Gfx/engine.cpp \
    src/Gfx/Exceptions/sdlexception.cpp \
    src/Tetris/game.cpp

CONFIG += c++11

LIBS += -lSDL2
LIBS += -lSDL2_image

HEADERS += \
    include/utils.h \
    include/Config/config.h \
    include/Config/readexception.h \
    include/Logger/logger.h \
    include/Logger/loglevel.h \
    include/globals.h \
    include/Config/writeexception.h \
    include/Gfx/engine.h \
    include/defaults.h \
    include/Gfx/Exceptions/sdlexception.h \
    include/Tetris/game.h
