#include "Piece.h"
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <fmt/core.h> 
#include <string>
#include <fmt/format.h>



Piece::Piece(PieceColor c, std::string n, SDL_Renderer* r, std::string style) : color(c), name(n){
    texture = IMG_LoadTexture(r, getImagePath(style).c_str());
    if (texture == NULL) {
        fmt::print("Error creating texture: ", SDL_GetError());
        return;
    }
}

SDL_Texture* Piece::GetTexture() {return texture;}

std::string Piece::getImagePath(std::string style) {
    std::string piecesDir = "res/images/lichess-org piece sets";
    std::string filename(fmt::format("{}{}.svg", (color == PieceColor::White) ? "w" : "b", name));
    return fmt::format("{}/{}/{}", piecesDir, style, filename);
}
std::string Piece::printPiece(){
    if (color == PieceColor::None){
        return "-";
    }
    return fmt::format("{}-{}", (color == PieceColor::White) ? "white" : "black", name);
}