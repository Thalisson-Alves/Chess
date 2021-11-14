#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "SFML/Graphics.hpp"
#include "memory"


class Piece : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    typedef std::unique_ptr<Piece> Ptr;

    enum Type {
        None = 0,
        King,
        Queen,
        Bishop,
        Knight,
        Rook,
        Pawn,

        NoColor = 7,
        White = 8,
        Black = 16
    };

    struct Move {
        enum class Type {None, Normal, Attack};

        int fromPosition, toPosition;
        Move::Type type;
    };

public:
    Piece(const sf::Texture &texture, Piece::Type type, int position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setSpritePosition(float x, float y);
    void resetSpritePosition();

    const Piece::Type &getType() const;
    bool isEnemy(const Piece::Ptr &piece) const;

    virtual std::vector<Move> getLegalMoves(const std::array<Piece::Ptr, 64> &pieces) const = 0;
    void setPosition(int index);

protected:
    Type Type;
    sf::Sprite Sprite;
    int Position;
    bool HasMoved;
};


#endif //CHESS_PIECE_H
