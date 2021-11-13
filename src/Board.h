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

    void update(const sf::Window &window);

private:
    std::array<Piece::Ptr, 64> Pieces;
    int SelectedPieceIndex;
    enum Piece::Type Turn;

    void loadPiecesFromFen(const sf::Texture &texture, const std::string &fenString);

    static void drawBackground(sf::RenderTarget &target, const sf::RenderStates &states);
    void drawPieces(sf::RenderTarget &target, sf::RenderStates &states) const;
    void drawSelectedPieceMoves(sf::RenderTarget &target, const sf::RenderStates &states) const;

    bool hasSelectedPiece() const;

};


#endif //CHESS_BOARD_H
