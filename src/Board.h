#pragma once

#include <string>
#include "Piece.h"

class Board{
public:
    Board(std::string fen);
private:
    Piece pieces[8][8];
};