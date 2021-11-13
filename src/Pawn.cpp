#include "Pawn.h"

Pawn::Pawn(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> Pawn::getLegalMoves() const {
    return std::vector<Piece::Move>();
}
