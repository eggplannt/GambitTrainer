#pragma once
#include <filesystem>
#include <string>
class Piece{
public:
    enum class PieceColor { White, Black, None };

    Piece(PieceColor c, std::string n) : color(c), name(n){};
    Piece() : color(PieceColor::None), name("") {}
    std::string getImagePath();
    std::string printPiece();
    PieceColor color;
    std::string name;
private:
    static const std::string piecesDir;
};