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
    src/Tetris/game.cpp \
    src/Tetris/Ui/gameui.cpp \
    src/Gfx/fontmanager.cpp \
    src/Gfx/Exceptions/unknownfontexception.cpp \
    src/Gfx/textwriter.cpp \
    src/Tetris/tile.cpp \
    src/Tetris/map.cpp \
    src/Tetris/maprenderer.cpp \
    src/Gfx/assetsmanager.cpp \
    src/Gfx/Exceptions/invalidmanifestexception.cpp \
    src/Tetris/tilefactory.cpp \
    src/Tetris/Collisions/abstractcollisionchecker.cpp \
    src/Tetris/Collisions/wallcollisionchecker.cpp \
    src/Tetris/movementmanager.cpp \
    src/Tetris/Collisions/mapcollisionchecker.cpp \
    src/Tetris/Ui/nexttilerenderer.cpp \
    src/Tetris/blockdrawer.cpp \
    src/Tetris/player.cpp

CONFIG += c++11

LIBS += -lSDL2
LIBS += -lSDL2_image
LIBS += -lSDL2_ttf

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
    include/Tetris/game.h \
    include/Tetris/Ui/gameui.h \
    include/Gfx/fontmanager.h \
    include/Gfx/font.h \
    include/Gfx/Exceptions/unknownfontexception.h \
    include/Gfx/textwriter.h \
    include/Tetris/tile.h \
    include/Tetris/enums.h \
    include/Tetris/map.h \
    include/Tetris/maprenderer.h \
    include/Gfx/assetsmanager.h \
    include/Gfx/Exceptions/invalidmanifestexception.h \
    include/Tetris/tilefactory.h \
    include/Tetris/Collisions/abstractcollisionchecker.h \
    include/Tetris/Collisions/wallcollisionchecker.h \
    include/Tetris/movementmanager.h \
    include/Tetris/Collisions/mapcollisionchecker.h \
    include/Tetris/Ui/nexttilerenderer.h \
    include/Tetris/blockdrawer.h \
    include/Tetris/player.h
