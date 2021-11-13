#include "Bishop.h"

Bishop::Bishop(const sf::Texture &texture, enum Piece::Type type, int position) :
        Piece(texture, type, position) {}

std::vector<Piece::Move> Bishop::getLegalMoves() const {
    return std::vector<Piece::Move>();
}
