#pragma once

#include <string>
#include "Piece.h"
#include <SDL3/SDL_surface.h > 
#include <SDL3_image/SDL_image.h>
#include <fmt/base.h>
#include <map>
#include <iostream>

const int BOARDSIZE = 480;


class Board{
public:
    Board(std::string fen);
    void printGrid();
    void renderBoard(SDL_Renderer* render);
private:
    Piece pieces[8][8];
};
