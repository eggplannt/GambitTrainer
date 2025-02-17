#pragma once

#include <string>
#include "Piece.h"
#include <SDL3/SDL_surface.h> 


class Board{
public:
    Board(std::string fen, SDL_Renderer*, float);
    ~Board();
    void printGrid();
    void DrawBoard();
private:
    float boardSize;
    Piece pieces[8][8];
    SDL_Renderer* renderer;
};
