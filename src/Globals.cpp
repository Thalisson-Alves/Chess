#include "Globals.h"

const int Config::BoardSize = 8;
const int Config::WindowWidth = 640;
const int Config::WindowHeight = 640;

float Config::getTileWidth() {
    return static_cast<float>(WindowWidth) / static_cast<float>(BoardSize);
}

float Config::getTileHeight() {
    return static_cast<float>(WindowHeight) / static_cast<float>(BoardSize);
}

bool Utils::isInBoardRange(int x, int y) {
    return (0 <= x && x < Config::BoardSize) && (0 <= y && y < Config::BoardSize);
}

sf::IntRect Utils::getSpriteRect(const enum Piece::Type &type) {
    if (type == Piece::Type::None)
        return {};

    const int spriteTotalSize = 200;
    const int spriteOffset = 10;
    const int spriteSize = spriteTotalSize - spriteOffset * 2;

    return {((type & Piece::Type::NoColor) - 1) * spriteTotalSize + spriteOffset,
            ((type & Piece::Type::Black) != 0) * spriteTotalSize + spriteOffset,
            spriteSize, spriteSize};
}
