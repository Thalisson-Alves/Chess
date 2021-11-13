#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "SFML/Graphics.hpp"
#include "Piece.h"

class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    explicit Board(const sf::Texture &texture,
                   const std::string &fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void selectPiece(int index);

private:
    std::array<Piece::Ptr, 64> Pieces;
    enum Piece::Type Turn;

    void loadPiecesFromFen(const sf::Texture &texture, const std::string &fenString);

    static void drawBackground(sf::RenderTarget &target, const sf::RenderStates &states);
};


#endif //CHESS_BOARD_H
