#include "Piece.h"
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>

Piece::Piece(PieceColor c, std::string n, SDL_Renderer *r, std::string theme)
    : color(c), name(n) {
  ChangeTheme(r, theme);
}

void Piece::ChangeTheme(SDL_Renderer *r, std::string theme) {
  SDL_Surface *surface = IMG_LoadSizedSVG_IO(
      SDL_IOFromFile(getImagePath(theme).c_str(), "r"), 256, 256);
  texture = SDL_CreateTextureFromSurface(r, surface);
  SDL_DestroySurface(surface);
  if (texture == NULL) {
    fmt::print("Error creating texture: {}", SDL_GetError());
    return;
  }
}
void Piece::Destroy(){
    SDL_DestroyTexture(texture);
}
SDL_Texture* Piece::GetTexture() {return texture;}

std::string Piece::getImagePath(std::string theme) {
  std::string piecesDir = "res/images/lichess-org piece sets";
  std::string filename(
      fmt::format("{}{}.svg", (color == PieceColor::White) ? "w" : "b", name));
  return fmt::format("{}/{}/{}", piecesDir, theme, filename);
}
std::string Piece::printPiece(){
    if (color == PieceColor::None){
        return "-";
    }
    return fmt::format("{}-{}", (color == PieceColor::White) ? "white" : "black", name);
}