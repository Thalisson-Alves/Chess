#include "Knight.h"

Knight::Knight(const sf::Texture &texture, enum Piece::Type type, int position) :
        Piece(texture, type, position) {

}

std::vector<Piece::Move> Knight::getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const {
    return std::vector<Piece::Move>();
}
