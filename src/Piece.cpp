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
        Position(position), Type(type), hasMoved(false), IsSelected(false), Sprite(texture, getSpriteRect(type)) {
    auto tileWidth = Config::getTileWidth();
    auto tileHeight = Config::getTileHeight();
    int x = Position % Config::BoardSize;
    int y = Position / Config::BoardSize;

    const auto &localBounds = Sprite.getLocalBounds();
    Sprite.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
    Sprite.setScale(0.45, 0.45);
    Sprite.setPosition(x * tileWidth + tileWidth / 2.0f, y * tileHeight + tileHeight / 2.0f);
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(Sprite, states);
}

const enum Piece::Type &Piece::getType() const {
    return Type;
}

void Piece::toggleSelect() {
    IsSelected = not IsSelected;
}
