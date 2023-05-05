#include <bits/stdc++.h>
#include "Menu.h"
using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[])
{
    initSDL(window, renderer, 1200, 800, "Endless Wizard");
    openMenu(window, renderer, 1200, 800);
    return 0;
}


