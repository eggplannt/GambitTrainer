#pragma once
#include <SDL3/SDL_render.h>
#include <string>
class Piece{
public:
    enum class PieceColor { White, Black, None };

    Piece(PieceColor, std::string, SDL_Renderer*, std::string);
    Piece() : color(PieceColor::None), name("") {}
    void Destroy();
    SDL_Texture* GetTexture();
    void ChangeTheme(SDL_Renderer *, std::string);
    std::string printPiece();
    PieceColor color;
    std::string name;
private:
    std::string getImagePath(std::string);
    SDL_Texture* texture;
};