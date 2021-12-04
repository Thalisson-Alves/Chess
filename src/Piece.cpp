#include "Piece.h"
#include "Globals.h"

Piece::Piece(const sf::Texture &texture, enum Type type, int position) :
        Position(position), Type(type), MoveCount(0), Sprite(texture, Utils::getSpriteRect(type)) {
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

void Piece::pushMovesByDirection(const std::array<Piece::Ptr, 64> &pieces, std::vector<Piece::Move> &moves,
                                 int xOffset, int yOffset, int limit) const {
    int x = Position % 8 + xOffset;
    int y = Position / 8 + yOffset;
    int counter = 0;

    while (Utils::isInBoardRange(x, y) && counter < limit && pieces[x + 8 * y]->getType() == Piece::Type::None) {
        moves.push_back({Position, x + 8 * y, Piece::Move::Type::Normal});
        x += xOffset;
        y += yOffset;
        counter++;
    }

    if (Utils::isInBoardRange(x, y) && counter < limit && isEnemy(pieces[x + 8 * y]))
        moves.push_back({Position, x + 8 * y, Piece::Move::Type::Attack});
}
