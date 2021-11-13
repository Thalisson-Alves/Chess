#include "Queen.h"

Queen::Queen(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Queen::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    return std::vector<Piece::Move>();
}
