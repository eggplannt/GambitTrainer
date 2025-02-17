#pragma once

#include "Piece.h"
#include <SDL3/SDL_surface.h>
#include <map>
#include <string>

class Board {
public:
  Board(std::string fen, SDL_Renderer *, float, std::string);
  ~Board();
  void ChangeFenGui();
  void ChangeThemeGui();
  void UpdateToFen();
  void PrintGrid();
  void DrawBoard();

private:
  float boardSize;
  Piece pieces[8][8];
  std::string theme;
  std::map<char, Piece> fenMap;
  std::string fen;
  SDL_Renderer *renderer;
};
