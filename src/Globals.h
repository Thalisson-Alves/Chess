#ifndef CHESS_GLOBALS_H
#define CHESS_GLOBALS_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace Config {
    extern const int BoardSize;
    extern const int WindowWidth;
    extern const int WindowHeight;

    float getTileWidth();
    float getTileHeight();
}

#endif //CHESS_GLOBALS_H
