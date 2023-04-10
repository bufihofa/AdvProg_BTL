#include "Menu.h"
#include "NewGame.h"
#include <thread>
#include <chrono>

void createMainMenu();
void createPlayMenu();
void createMageMenu();
void createTrailMenu();
void createMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height);
int getMenuOpening(string buttonClicked);
void playButtonClicked(string buttonClicked);
void mageButtonClicked(string buttonClicked);
void trailtButtonClicked(string buttonClicked);
void renderMenuWindow();
void onMenuMouseMove(double x, double y);
void onMenuMouseClick(double x, double y);
void openMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height);
