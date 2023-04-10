#include "Menu.h"
#include "NewGame.h"
#include <thread>
#include <chrono>

Menu* mainMenu;
Menu* playMenu;
Menu* mageMenu;
Menu* trailMenu;
Entity* background;
Entity* pointer;

SDL_Window* mWindow;
SDL_Renderer* mRenderer;

int menuOpening = 1;

void createMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height){
    mWindow = window;
    mRenderer = renderer;

    pointer = new Entity(0, 300, "res/Menu/pointer.png", renderer);
    pointer->setScale(0.45);
    pointer->render();

    background = new Entity(0, 0, "res/Menu/MenuBackGround.png", renderer);
    background->setHW(_height, _width);

    mainMenu = new Menu(renderer);
    mainMenu->addButton("PlayMenu", 600, 700, "res/Menu/PlayButton.png", renderer, 1, false, true); //0
    mainMenu->addButton("MageMenu", 400, 700, "res/Menu/MageButton.png", renderer, 1, false, true); //1
    mainMenu->addButton("TrailMenu", 800, 700, "res/Menu/TrailButton.png", renderer, 1, false, true); //2


    playMenu = new Menu(renderer);
    playMenu->addButton("easy", 600, 150, "res/Menu/EasyMode.png", renderer, 0.5, false, true);
    playMenu->addButton("medium", 600, 350, "res/Menu/MediumMode.png", renderer, 0.5, false, true);
    playMenu->addButton("hard", 600, 550, "res/Menu/HardMode.png", renderer, 0.5, false, true);

    mageMenu = new Menu(renderer);
    mageMenu->addButton("d1", 600, 150, "res/Menu/EasyMode.png", renderer, 0.3, false, true);
    mageMenu->addButton("d2", 600, 350, "res/Menu/MediumMode.png", renderer, 0.3, false, true);
    mageMenu->addButton("d3", 600, 550, "res/Menu/HardMode.png", renderer, 0.3, false, true);

    trailMenu = new Menu(renderer);
    trailMenu->addButton("f1", 600, 150, "res/Menu/EasyMode.png", renderer, 0.3, false, true);
    trailMenu->addButton("f2", 600, 350, "res/Menu/MediumMode.png", renderer, 0.3, false, true);
    trailMenu->addButton("f3", 600, 550, "res/Menu/HardMode.png", renderer, 0.3, false, true);

}
int getMenuOpening(string buttonClicked){
    if     (buttonClicked == "PlayMenu") return 1;
    else if(buttonClicked == "MageMenu") return 2;
    else if(buttonClicked == "TrailMenu") return 3;
    return 0;
}
void playButtonClicked(string buttonClicked){
    if(buttonClicked == "easy"){
        newGame(mWindow, mRenderer, 1);
        return;
    }
    else if (buttonClicked == "medium"){
        newGame(mWindow, mRenderer, 2);
        return;
    }
    else if (buttonClicked == "hard"){
        newGame(mWindow, mRenderer, 3);
        return;
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

    pointer->setAngle(pointer->getAngle()+3);
    pointer->renderCenter();

    SDL_RenderPresent(mRenderer);
}
void openMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height){
    const int PLAY_MENU = 1;
    const int MAGE_MENU = 2;
    const int TRAILT_MENU = 3;


    if(background == NULL){
        createMenu(window, renderer, _width, _height);
    }

    SDL_Event ev;
    int FPS = 60;
    int frameDelay = 1000 / FPS;
    int frameTime = 0;

    while(true){
        frameTime = SDL_GetTicks();
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT) return;

            if(ev.type == SDL_MOUSEMOTION){
                pointer->setXY(ev.button.x , ev.button.y);
                mainMenu->onMouseMove(ev.button.x , ev.button.y);

                switch(menuOpening){
                case PLAY_MENU:
                    playMenu->onMouseMove(ev.button.x , ev.button.y);
                    break;
                case MAGE_MENU:
                    mageMenu->onMouseMove(ev.button.x , ev.button.y);
                    break;
                case TRAILT_MENU:
                    trailMenu->onMouseMove(ev.button.x , ev.button.y);
                    break;
                }
            }
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                switch(menuOpening){
                case PLAY_MENU:
                    playButtonClicked(playMenu->getButtonClicked(ev.button.x , ev.button.y));
                    break;
                case MAGE_MENU:
                    mageButtonClicked(mageMenu->getButtonClicked(ev.button.x , ev.button.y));
                    break;
                case TRAILT_MENU:
                    trailtButtonClicked(trailMenu->getButtonClicked(ev.button.x , ev.button.y));
                    break;
                }
                menuOpening = getMenuOpening(mainMenu->getButtonClicked(ev.button.x , ev.button.y));
                mainMenu->forceUnHL();
            }
        }

        renderMenuWindow();

        frameTime = frameDelay - SDL_GetTicks() + frameTime;
        if(frameTime>0) this_thread::sleep_for(chrono::milliseconds(frameTime));
    }

}




