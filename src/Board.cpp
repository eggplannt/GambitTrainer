#include "Board.h"


void Board::printGrid() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fmt::print("{} ", pieces[j][i].printPiece());
        }
        fmt::print("\n");
    }

}

void Board::renderBoard(SDL_Renderer* render) {
    SDL_Texture* boardTexture = IMG_LoadTexture(render, "res/images/board.png");
    if (boardTexture == NULL) {
        std::cout << "Error loading image: " << SDL_GetError();
        return;
    }
    

    SDL_FRect rect = { 0, 0, 480, 480};
    SDL_RenderTexture(render, boardTexture, 0, &rect);
    int squareSize = BOARDSIZE / 8;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (pieces[x][y].name == "") {
                continue;
            }

            SDL_Texture* pieceTexture = IMG_LoadTexture(render, pieces[x][y].getImagePath().c_str());
            if (pieceTexture == NULL) {
                std::cout << "Error loading image: " << SDL_GetError();
                return;
            }

            SDL_SetTextureBlendMode(pieceTexture, SDL_BLENDMODE_BLEND);

            SDL_FRect pieceRect = { squareSize*x, squareSize*y, squareSize, squareSize };
            SDL_RenderTexture(render, pieceTexture, 0, &pieceRect);
            
        }
    }
}

Board::Board(std::string fen) : pieces{} {
    std::map<char, Piece> fenMap;

    fenMap['r'] = Piece(Piece::PieceColor::Black, "rook");
    fenMap['R'] = Piece(Piece::PieceColor::White, "rook");
    fenMap['n'] = Piece(Piece::PieceColor::Black, "knight");
    fenMap['N'] = Piece(Piece::PieceColor::White, "knight");
    fenMap['b'] = Piece(Piece::PieceColor::Black, "bishop");
    fenMap['B'] = Piece(Piece::PieceColor::White, "bishop");
    fenMap['q'] = Piece(Piece::PieceColor::Black, "queen");
    fenMap['Q'] = Piece(Piece::PieceColor::White, "queen");
    fenMap['k'] = Piece(Piece::PieceColor::Black, "king");
    fenMap['K'] = Piece(Piece::PieceColor::White, "king");
    fenMap['p'] = Piece(Piece::PieceColor::Black, "pawn");
    fenMap['P'] = Piece(Piece::PieceColor::White, "pawn");

    int x = 0;
    int y = 0;
    for (char s : fen){
        if (fenMap.count(s)){
            pieces[x][y] = fenMap[s];
            // fmt::print("{} ({}, {})", pieces[x][y].printPiece(), x, y);

            x++;
        }
        else if (s == '/'){
            y++;
            x = 0;
        }
        else if (s == ' '){
            break;
        }
        else{
            x += s-'0';
        }
    }
}
