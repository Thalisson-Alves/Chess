#include "King.h"

King::King(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> King::getLegalMoves() const {
    return std::vector<Piece::Move>();
}
