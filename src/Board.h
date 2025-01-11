#pragma once

#include <string>
#include "Piece.h"

class Board{
public:
    Board(std::string fen);
    void printGrid();
private:
    Piece pieces[8][8];
};