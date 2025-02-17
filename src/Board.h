#pragma once

#include <string>
#include "Piece.h"
#include <SDL3/SDL_surface.h> 

const float BOARDSIZE = 480;


class Board{
public:
    Board(std::string fen, SDL_Renderer*);
    void printGrid();
    void renderBoard();
private:
    Piece pieces[8][8];
    SDL_Renderer* renderer;
};
