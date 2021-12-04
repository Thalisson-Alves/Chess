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

    void movePieceToPosition(int positionIndex);

    bool hasSelectedPiece() const;

    enum Piece::Type getPromotionColor() const;

    void promoteTo(enum Piece::Type pieceType);

private:
    void loadPiecesFromFen(const sf::Texture &texture, const std::string &fenString);

    static void drawBackground(sf::RenderTarget &target, const sf::RenderStates &states);

    void drawPieces(sf::RenderTarget &target, sf::RenderStates &states) const;

    void drawSelectedPieceMoves(sf::RenderTarget &target, const sf::RenderStates &states) const;

    void deselectPiece();

    void movePiece(Piece::Move move);

    void updateTurn();

    std::array<Piece::Ptr, 64> Pieces;
    int SelectedPieceIndex;
    enum Piece::Type Turn;

    int PromotionIndex;
    const sf::Texture &Texture;
};


#endif //CHESS_BOARD_H
