#include "Rook.h"

Rook::Rook(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Rook::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    return std::vector<Piece::Move>();
}
