#pragma once
#include <filesystem>
#include <string>
class Piece{
public:
    enum class PieceColor { White, Black, None };

    Piece(PieceColor c, std::string n) : color(c), name(n){};
    Piece() : color(PieceColor::None), name("") {}
    std::filesystem::path getImagePath();
    std::string printPiece();
private:
    PieceColor color;
    std::string name;
    static const std::filesystem::path piecesDir;
};