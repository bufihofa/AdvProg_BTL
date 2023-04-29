#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_utils.h"
#include "Menu.h"
using namespace std;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "Test";



int main(int argc, char* argv[])
{

    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    //Open Game Menu -> MainMenu.cpp
    openMenu(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //newGame(window, renderer, 1);
    //quitSDL(window, renderer);
    return 0;
}


