#include "Piece.h"
#include <filesystem>
#include <fmt/core.h> 
#include <string>
#include <fmt/format.h>


const std::string Piece::piecesDir("res/images/pieces");

std::string Piece::getImagePath() {
    std::string filename(fmt::format("{}-{}.png", (color == PieceColor::White) ? "white" : "black", name));
    return fmt::format("{}/{}", piecesDir, filename);
}
std::string Piece::printPiece(){
    if (color == PieceColor::None){
        return "-";
    }
    return fmt::format("{}-{}", (color == PieceColor::White) ? "white" : "black", name);
}