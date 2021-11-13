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

public:
    Piece(const sf::Texture &texture, Piece::Type type, int position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const Piece::Type &getType() const;

    void select();
    void deselect();

    void update(const sf::Window &window);

private:
    Type Type;
    sf::Sprite Sprite;
    int Position;
    bool hasMoved;
    bool IsSelected;

    void resetSpritePosition();
};


#endif //CHESS_PIECE_H
