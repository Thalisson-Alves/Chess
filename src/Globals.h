#ifndef CHESS_GLOBALS_H
#define CHESS_GLOBALS_H

#include <SFML/Graphics/Rect.hpp>
#include "Piece.h"

namespace Config {
    extern const int BoardSize;
    extern const int WindowWidth;
    extern const int WindowHeight;

    float getTileWidth();

    float getTileHeight();
}

namespace Utils {
    bool isInBoardRange(int x, int y);

    sf::IntRect getSpriteRect(const enum Piece::Type &type);
}

#endif //CHESS_GLOBALS_H
