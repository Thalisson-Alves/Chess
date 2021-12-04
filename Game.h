#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <array>
#include "src/Board.h"

namespace Game {
    void Run();
    void drawPromotionPieces(const sf::Texture &texture, const enum Piece::Type &promotionColor, sf::RenderWindow &window);
    bool handlePromotion(Board &board, int selectedIndex);

    const std::array<enum Piece::Type, 4> PossiblePromotions{Piece::Queen, Piece::Bishop,
                                                             Piece::Rook, Piece::Knight};
};


#endif //CHESS_GAME_H
