#include <imgui.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <imgui.h>

#include <imgui_impl_sdlrenderer3.h>
#include <imgui_impl_sdl3.h>

#include "main.h"
#include "Board.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Surface* gHelloWorld = nullptr;

const std::string DEFAULTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
int main(int argc, char *args[]) {
  int exitCode = 0;


  init();
  std::cout << SDL_VERSION;
  if( !loadMedia() ) {
    SDL_Log( "Unable to load media!\n" );
    close();
    return -1;
  }

  gameLoop();
  close();
}

void gameLoop() {
  Board board(DEFAULTFEN, gRenderer, 720);
  board.printGrid();

  bool quit = false;
  SDL_Event e;
  SDL_zero(e);
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      ImGui_ImplSDL3_ProcessEvent(&e);
      if (e.type == SDL_EVENT_QUIT)
        quit = true;
    }
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    SDL_SetRenderDrawColor(gRenderer,0, 0, 0, 0);
    SDL_RenderClear(gRenderer);
    board.DrawBoard();
    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), gRenderer);
    SDL_RenderPresent(gRenderer);
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
    720,
    720,
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
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();
  ImGui_ImplSDL3_InitForSDLRenderer(gWindow, gRenderer);
  ImGui_ImplSDLRenderer3_Init(gRenderer);
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



