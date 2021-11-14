#ifndef CHESS_GLOBALS_H
#define CHESS_GLOBALS_H

namespace Config {
    extern const int BoardSize;
    extern const int WindowWidth;
    extern const int WindowHeight;

    float getTileWidth();

    float getTileHeight();
}

namespace Utils {
    bool isInBoardRange(int x, int y);
}

#endif //CHESS_GLOBALS_H
