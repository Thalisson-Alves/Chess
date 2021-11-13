#include "Rook.h"

Rook::Rook(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Rook::getLegalMoves() const {
    return std::vector<Piece::Move>();
}
