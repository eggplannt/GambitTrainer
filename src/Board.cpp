#include "Board.h"
#include "Piece.h"
#include <fmt/base.h>
#include <map>


void Board::printGrid() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fmt::print("{} ", pieces[j][i].printPiece());
        }
        fmt::print("\n");
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
