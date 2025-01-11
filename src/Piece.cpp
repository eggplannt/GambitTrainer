#include "Piece.h"
#include <filesystem>
#include <fmt/core.h> 
#include <string>


const std::filesystem::path Piece::piecesDir("/res/images/pieces");

std::filesystem::path Piece::getImagePath() {
    std::string filename(fmt::format("{}-{}.png", (color == PieceColor::White) ? "white" : "black", name));
    return std::filesystem::path(/*piecesDir */ filename);
}
std::string Piece::printPiece(){
    if (color == PieceColor::None){
        return "-";
    }
    return fmt::format("{}-{}", (color == PieceColor::White) ? "white" : "black", name);
}