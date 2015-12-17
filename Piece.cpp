//
// Created by Stephen on 12/10/2015.
//

#include "Piece.h"

unsigned int Gaming::Piece::__idGen = 0;

Gaming::Piece::Piece(const Gaming::Game &g, const Gaming::Position &p) : __finished(false), __turned(false), __position(p), __game(g), __id(__idGen++)
{
}

Gaming::Piece::~Piece() {
    //__idGen--;
}

Gaming::PieceType getType() { return Gaming::PieceType::EMPTY; }

namespace Gaming {
    std::ostream &operator<<(std::ostream &os, const Piece &piece){
        piece.print(os);
        os << piece.__id;
        return os;    //TODO - Implement this
    }
}
