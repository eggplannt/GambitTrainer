

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <fmt/base.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <map>
#include <string>

#include "Board.h"
#include "Piece.h"
void Board::PrintGrid() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      fmt::print("{} ", pieces[j][i].printPiece());
    }
    fmt::print("\n");
  }
}

void Board::DrawBoard() {

  SDL_Texture *boardTexture =
      IMG_LoadTexture(renderer, "res/images/lichess-org board sets/brown.png");
  if (boardTexture == NULL) {
    fmt::print("Error creating Texture: {}\n", SDL_GetError());
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

      if (theme == "pixel") {
        SDL_SetTextureScaleMode(pieceTexture,
                                SDL_SCALEMODE_NEAREST); // Prevents smoothing
      }

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
Board::Board(std::string f, SDL_Renderer *r, float b, std::string t)
    : pieces{}, renderer(r), boardSize(b), theme(t) {

  fenMap['r'] = Piece(Piece::PieceColor::Black, "R", r, theme);
  fenMap['R'] = Piece(Piece::PieceColor::White, "R", r, theme);
  fenMap['n'] = Piece(Piece::PieceColor::Black, "N", r, theme);
  fenMap['N'] = Piece(Piece::PieceColor::White, "N", r, theme);
  fenMap['b'] = Piece(Piece::PieceColor::Black, "B", r, theme);
  fenMap['B'] = Piece(Piece::PieceColor::White, "B", r, theme);
  fenMap['q'] = Piece(Piece::PieceColor::Black, "Q", r, theme);
  fenMap['Q'] = Piece(Piece::PieceColor::White, "Q", r, theme);
  fenMap['k'] = Piece(Piece::PieceColor::Black, "K", r, theme);
  fenMap['K'] = Piece(Piece::PieceColor::White, "K", r, theme);
  fenMap['p'] = Piece(Piece::PieceColor::Black, "P", r, theme);
  fenMap['P'] = Piece(Piece::PieceColor::White, "P", r, theme);

  fen = f;
  UpdateToFen();
}
void Board::UpdateToFen() {
  int x = 0;
  int y = 0;
  for (char s : fen) {
    if (fenMap.count(s)) {
      pieces[x][y] = fenMap[s];
      x++;
    } else if (s == '/') {
      y++;
      x = 0;
    } else if (s == ' ') {
      return;
    } else {
      int count = s - '0';
      for (int i = 0; i < count; i++) {
        pieces[x][y] = Piece();
        x++;
      }
    }
  }
}

void Board::ChangeFenGui() {
  ImGui::SetNextWindowSize(ImVec2(300, 100));
  ImGui::SetNextWindowPos(ImVec2(100, 50));

  ImGui::Begin("Change Fen");
  ImGui::InputText("Fen", &fen);
  if (ImGui::Button("Set"))
    UpdateToFen();

  ImGui::End();
}

void Board::ChangeThemeGui() {
  ImGui::SetNextWindowSize(ImVec2(300, 100));
  ImGui::SetNextWindowPos(ImVec2(500, 50));
  ImGui::Begin("Change Theme");
  ImGui::InputText("Theme", &theme);
  if (ImGui::Button("Set")) {
    for (auto i : fenMap) {
      fenMap[i.first].ChangeTheme(renderer, theme);
    }
    UpdateToFen();
  }
  ImGui::End();
}
