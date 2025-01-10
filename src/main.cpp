#include "main.h"
#include "Board.h"
#include <string>

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Surface* gHelloWorld = nullptr;

const int BOARDSIZE = 480;
const std::string DEFAULTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main( int argc, char* args[] ) {
  int exitCode = 0;


  init();
  if( !loadMedia() ) {
    SDL_Log( "Unable to load media!\n" );
    close();
    return -1;
  }

  Board board(DEFAULTFEN);
  bool quit = false;
  SDL_Event e;
  SDL_zero(e);
  while( quit == false ) {
    while( SDL_PollEvent( &e ) ) {
      if( e.type == SDL_EVENT_QUIT ) quit = true;
      SDL_RenderClear(gRenderer);
      basicRenderBoard();

      SDL_RenderPresent(gRenderer);

    }
    
  }
  close();
}

void basicRenderBoard(){
  bool isWhite = true;
  int white[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  int black[4] = {0, 0, 0, 0xFF};
  int* color = white;
  float squareSize = BOARDSIZE/float(8);

  for (int y = 0; y < 8; y++){
    isWhite = !isWhite;
    if (isWhite) color = white;
    else color = black;
    for (int x = 0; x < 8 ; x++){
      SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], color[4]);
      SDL_FRect rect{
        x*squareSize, 
        y*squareSize,
        squareSize,
        squareSize
      };
      SDL_RenderFillRect(gRenderer, &rect);

      isWhite = !isWhite;
      if (isWhite) color = white;
      else color = black;

    }
  }
}
void close() {
  SDL_DestroySurface( gHelloWorld );
  gHelloWorld = nullptr;
  
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;

  SDL_Quit();
}
void init() {

  if ( SDL_Init(SDL_INIT_VIDEO) == false){
    SDL_Log("SDL_Init: %s", SDL_GetError());
    close();
    exit(-1);
  }

  gWindow = SDL_CreateWindow(
    "GambitTrainer",
    480,
    480,
    0
  );
  if (gWindow == nullptr){
    SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
    close();
    exit(-1);
  }
  gRenderer = SDL_CreateRenderer(gWindow, NULL);
  if (gRenderer == nullptr){
    SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
    close();
    exit(-1);
  }
}

bool loadMedia()
{
    bool success{ true };

    std::string imagePath{ "res/images/sdl.bmp" };
    if( gHelloWorld = SDL_LoadBMP( imagePath.c_str() ); gHelloWorld == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success = false;
    }

    return success;
}



