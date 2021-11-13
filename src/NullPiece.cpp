#include "NullPiece.h"

NullPiece::NullPiece(const sf::Texture &texture, enum Piece::Type type, int position) : Piece(texture, type, position) {

}

std::vector<Piece::Move> NullPiece::getLegalMoves() const {
    return {};
}
