#include "Piece.h"
#include "Globals.h"

sf::IntRect getSpriteRect(const enum Piece::Type &type) {
    if (type == Piece::Type::None)
        return {};

    const int spriteTotalSize = 200;
    const int spriteOffset = 10;
    const int spriteSize = spriteTotalSize - spriteOffset * 2;

    return {((type & Piece::Type::NoColor) - 1) * spriteTotalSize + spriteOffset,
            ((type & Piece::Type::Black) != 0) * spriteTotalSize + spriteOffset,
            spriteSize, spriteSize};
}

Piece::Piece(const sf::Texture &texture, enum Type type, int position) :
        Position(position), Type(type), MoveCount(0), Sprite(texture, getSpriteRect(type)) {
    const auto &localBounds = Sprite.getLocalBounds();
    Sprite.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
    Sprite.setScale(0.45, 0.45);

    resetSpritePosition();
}

void Piece::resetSpritePosition() {
    auto tileWidth = Config::getTileWidth();
    auto tileHeight = Config::getTileHeight();
    int x = Position % Config::BoardSize;
    int y = Position / Config::BoardSize;

    Sprite.setPosition(x * tileWidth + tileWidth / 2.0f, y * tileHeight + tileHeight / 2.0f);
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(Sprite, states);
}

const enum Piece::Type &Piece::getType() const {
    return Type;
}

void Piece::setSpritePosition(float x, float y) {
    Sprite.setPosition(x, y);
}

bool Piece::isEnemy(const Piece::Ptr &piece) const {
    return piece->Type && !((piece->Type & Type) & (~Piece::Type::NoColor));
}

void Piece::setPosition(int index) {
    Position = index;
    resetSpritePosition();
    MoveCount++;
}

int Piece::getMoveCount() const {
    return MoveCount;
}
