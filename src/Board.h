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

    static void movePiece(std::array<Piece::Ptr, 64> &pieces, Piece::Move move);

    void updateTurn();

    static bool isInCheck(const std::array<Piece::Ptr, 64> &pieces, enum Piece::Type color);

    Piece::Ptr createPieceForType(enum Piece::Type pieceType, int position) const;

    bool makeMove(std::array<Piece::Ptr, 64> &pieces, Piece::Move move) const;

    std::array<Piece::Ptr, 64> evaluateMove(Piece::Move move) const;

    std::vector<Piece::Move> filterByCheck(const std::vector<Piece::Move> &moves, enum Piece::Type color) const;

    std::array<Piece::Ptr, 64> Pieces;
    int SelectedPieceIndex;
    enum Piece::Type Turn;

    int PromotionIndex;
    const sf::Texture &Texture;
};


#endif //CHESS_BOARD_H
