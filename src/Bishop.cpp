#include "Bishop.h"

Bishop::Bishop(const sf::Texture &texture, enum Piece::Type type, int position) :
        Piece(texture, type, position) {}

std::vector<Piece::Move> Bishop::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    return {};
}
