#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <string>

SDL_Window* gWindow = nullptr;
    
SDL_Surface* gScreenSurface = nullptr;

SDL_Surface* gHelloWorld = nullptr;


void close() {
  SDL_DestroySurface( gHelloWorld );
  gHelloWorld = nullptr;
  
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;
  gScreenSurface = nullptr;

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
    640,
    480,
    0
  );
  if (gWindow == nullptr){
    SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
    close();
    exit(-1);
  }
  gScreenSurface = SDL_GetWindowSurface(gWindow);
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



int main( int argc, char* args[] ) {
  int exitCode = 0;

  //Initialize
  init();
  if( !loadMedia() ) {
    SDL_Log( "Unable to load media!\n" );
    close();
    return -1;
  }
  bool quit = false;

  //The event data
  SDL_Event e;
  SDL_zero(e);
  while( quit == false ) {
    while( SDL_PollEvent( &e ) ) {
      if( e.type == SDL_EVENT_QUIT ) quit = true;
      SDL_FillSurfaceRect( gScreenSurface, nullptr, SDL_MapSurfaceRGB( gScreenSurface, 0, 0xFF, 0 ) );

      // SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr );

      SDL_UpdateWindowSurface( gWindow );
    }
    
  }
  close();
}
