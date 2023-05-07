
#include "MainMenu.h"
#include "Menu.h"
#include "NewGame.h"
Menu* mainMenu = NULL;
Menu* playMenu = NULL;
Menu* mageMenu = NULL;
Menu* trailMenu = NULL;
Entity* background = NULL;
Entity* pointer = NULL;

SDL_Window* mWindow = NULL;
SDL_Renderer* mRenderer = NULL;
bool MENU = false;
const int PLAY_MENU = 1;
const int MAGE_MENU = 2;
const int TRAILT_MENU = 3;

int menuOpening = 1;

Mix_Chunk* clickWav = NULL;

int getMenuOpening(string buttonClicked){
    if     (buttonClicked == "PlayMenu") return 1;
    else if(buttonClicked == "MageMenu") return 2;
    else if(buttonClicked == "TrailMenu") return 3;
    return menuOpening;
}
void createMainMenu(){
    clickWav = Mix_LoadWAV("res/wav/click.wav");
    mainMenu = new Menu(mRenderer);
    mainMenu->addButton("PlayMenu", 600, 700, "res/Menu/PlayButton.png", mRenderer, 1, true);
    mainMenu->addButton("MageMenu", 400, 700, "res/Menu/MageButton.png", mRenderer, 1, true);
    mainMenu->addButton("TrailMenu", 800, 700, "res/Menu/TrailButton.png", mRenderer, 1, true);
}
void createPlayMenu(){
    playMenu = new Menu(mRenderer);
    playMenu->addButton("easy", 600, 200, "res/Menu/easy.png", mRenderer, 0.45, true);
    playMenu->addButton("medium", 600, 350, "res/Menu/normal.png", mRenderer, 0.45, true);
    playMenu->addButton("hard", 600, 500, "res/Menu/hard.png", mRenderer, 0.45, true);
}
void createMageMenu(){
    mageMenu = new Menu(mRenderer);
    mageMenu->addButton("howtoplay", 600, 360, "res/Menu/howtoplay.png", mRenderer, 0.8, true);
}
void createTrailMenu(){
    trailMenu = new Menu(mRenderer);
    trailMenu->addButton("f1", 600, 150, "res/Menu/EasyMode.png", mRenderer, 0.3, true);
    trailMenu->addButton("f2", 600, 350, "res/Menu/MediumMode.png", mRenderer, 0.3, true);
    trailMenu->addButton("f3", 600, 550, "res/Menu/HardMode.png", mRenderer, 0.3, true);
}
void createMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height){
    mWindow = window;
    mRenderer = renderer;

    pointer = new Entity(0, 300, "res/Menu/pointer.png", renderer);
    pointer->setScale(0.45);

    background = new Entity(0, 0, "res/Menu/MenuBackGround.png", renderer);
    background->setHW(_height, _width);

    createMainMenu();
    createPlayMenu();
    createMageMenu();
    createTrailMenu();
}
void playButtonClicked(string buttonClicked){
    if(buttonClicked == "easy"){
        newGame(mWindow, mRenderer, 1);
        MENU = false;
    }
    else if (buttonClicked == "medium"){
        newGame(mWindow, mRenderer, 2);
        MENU = false;
    }
    else if (buttonClicked == "hard"){
        newGame(mWindow, mRenderer, 3);
        MENU = false;
    }
}
void mageButtonClicked(string buttonClicked){
    if(buttonClicked == "d1"){

    }
    else if (buttonClicked == "d2"){

    }
    else if (buttonClicked == "d3"){

    }
}
void trailtButtonClicked(string buttonClicked){
    if(buttonClicked == "f1"){

    }
    else if (buttonClicked == "f2"){

    }
    else if (buttonClicked == "f3"){

    }
}
void renderMenuWindow(){
    background->render();
    mainMenu->forceHL(menuOpening-1);
    mainMenu->render();
    if     (menuOpening == 1) playMenu->render();
    else if(menuOpening == 2) mageMenu->render();
    else if(menuOpening == 3) trailMenu->render();

    SDL_RenderPresent(mRenderer);
}
void onMenuMouseMove(double x, double y){
    mainMenu->onMouseMove(x , y);

    switch(menuOpening){
    case PLAY_MENU:
        playMenu->onMouseMove(x, y);
        break;
    case MAGE_MENU:
        mageMenu->onMouseMove(x, y);
        break;
    case TRAILT_MENU:
        trailMenu->onMouseMove(x, y);
        break;
    }
}
void onMenuMouseClick(double x, double y){
    switch(menuOpening){
    case PLAY_MENU:
        playButtonClicked(playMenu->getButtonClicked(x, y));
        break;
    case MAGE_MENU:
        mageButtonClicked(mageMenu->getButtonClicked(x, y));
        break;
    case TRAILT_MENU:
        trailtButtonClicked(trailMenu->getButtonClicked(x, y));
        break;
    }
    menuOpening = getMenuOpening(mainMenu->getButtonClicked(x, y));
    mainMenu->forceUnHL();
}

void openMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height){
    mWindow = window;
    mRenderer = renderer;
    if(mainMenu == NULL){
        createMenu(window, renderer, _width, _height);
    }
    //SDL_ShowCursor(0);
    SDL_Event ev;
    double FPS = 30;
    double frameDelay = 1000 / FPS;
    int frameTime = 0;
    MENU = true;
    while(MENU){
        frameTime = SDL_GetTicks();
        renderMenuWindow();
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                return;
            }

            if(ev.type == SDL_MOUSEMOTION){
                onMenuMouseMove(ev.button.x, ev.button.y);
            }
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                Mix_PlayChannel(-1, clickWav, 0);
                onMenuMouseClick(ev.button.x, ev.button.y);
            }
        }
        if(!MENU) return;
        frameTime = frameDelay - SDL_GetTicks() + frameTime;

        if(frameTime>0) this_thread::sleep_for(chrono::milliseconds(frameTime));

    }
}




