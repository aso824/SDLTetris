#ifndef ENUMS_H
#define ENUMS_H

namespace Tetris {
    enum TileType {
        I, T, O, L, J, S, Z
    };

    enum TileColors {
        TILE_COLOR_BLANK,
        TILE_COLOR_YELLOW,
        TILE_COLOR_CYAN,
        TILE_COLOR_GREEN,
        TILE_COLOR_ORANGE,
        TILE_COLOR_RED,
        TILE_COLOR_PURPLE,
        TILE_COLOR_BLUE
    };

    enum RotationDirection {
        ROTATE_LEFT,
        ROTATE_RIGHT
    };

    enum MovementDirection {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_DOWN
    };
}

#endif // ENUMS_H
