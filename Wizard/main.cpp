#include <bits/stdc++.h>
#include "Menu.h"
using namespace std;


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, 1200, 800, "Endless Wizard");
    openMenu(window, renderer, 1200, 800);
    return 0;
}


