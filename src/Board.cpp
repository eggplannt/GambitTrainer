#include "Board.h"

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <fmt/base.h>
#include <iostream>
#include <map>

void Board::printGrid() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      fmt::print("{} ", pieces[j][i].printPiece());
    }
    fmt::print("\n");
  }
}

void Board::DrawBoard() {
  SDL_Texture *boardTexture = IMG_LoadTexture(renderer, "res/images/board.png");
  if (boardTexture == NULL) {
    std::cout << "Error loading image: " << SDL_GetError();
    return;
  }

  SDL_FRect rect = {0, 0, boardSize, boardSize};
  SDL_RenderTexture(renderer, boardTexture, 0, &rect);
  SDL_DestroyTexture(boardTexture);
  float squareSize = boardSize / 8;

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (pieces[x][y].name == "") {
        continue;
      }

      SDL_Texture *pieceTexture = pieces[x][y].GetTexture();
      SDL_FRect pieceRect = {squareSize * x, squareSize * y, squareSize,
                             squareSize};
      SDL_RenderTexture(renderer, pieceTexture, NULL, &pieceRect);
    }
  }
}
Board::~Board() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pieces[x][y].Destroy();
    }
  }
}
Board::Board(std::string fen, SDL_Renderer *r, float b)
    : pieces{}, renderer(r), boardSize(b) {
  std::map<char, Piece> fenMap;

  fenMap['r'] = Piece(Piece::PieceColor::Black, "R", r, "alpha");
  fenMap['R'] = Piece(Piece::PieceColor::White, "R", r, "alpha");
  fenMap['n'] = Piece(Piece::PieceColor::Black, "N", r, "alpha");
  fenMap['N'] = Piece(Piece::PieceColor::White, "N", r, "alpha");
  fenMap['b'] = Piece(Piece::PieceColor::Black, "B", r, "alpha");
  fenMap['B'] = Piece(Piece::PieceColor::White, "B", r, "alpha");
  fenMap['q'] = Piece(Piece::PieceColor::Black, "Q", r, "alpha");
  fenMap['Q'] = Piece(Piece::PieceColor::White, "Q", r, "alpha");
  fenMap['k'] = Piece(Piece::PieceColor::Black, "K", r, "alpha");
  fenMap['K'] = Piece(Piece::PieceColor::White, "K", r, "alpha");
  fenMap['p'] = Piece(Piece::PieceColor::Black, "P", r, "alpha");
  fenMap['P'] = Piece(Piece::PieceColor::White, "P", r, "alpha");

  int x = 0;
  int y = 0;
  for (char s : fen) {
    if (fenMap.count(s)) {
      pieces[x][y] = fenMap[s];
      // fmt::print("{} ({}, {})", pieces[x][y].printPiece(), x, y);

      x++;
    } else if (s == '/') {
      y++;
      x = 0;
    } else if (s == ' ') {
      break;
    } else {
      x += s - '0';
    }
  }
}
