#include "Menu.h"
#include "NewGame.h"
#include <thread>
#include <chrono>
Menu* mainMenu;
Menu* playMenu;
Menu* mageMenu;
Menu* trailMenu;
Entity* background;
void openMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height){

    //khoi tao cac menu
    int menuIsOpen = 1;
    if(background == NULL){

        background = new Entity(0, 0, "res/Menu/MenuBackGround.png", renderer);
        background->setHW(800, 1200);
        //tao main menu va them cac button
        mainMenu = new Menu(renderer);
        mainMenu->addButton("PlayMenu", 600, 700, "res/Menu/PlayButton.png", renderer, 1, false, true); //0
        mainMenu->addButton("MageMenu", 400, 700, "res/Menu/MageButton.png", renderer, 1, false, true); //1
        mainMenu->addButton("TrailMenu", 800, 700, "res/Menu/TrailButton.png", renderer, 1, false, true); //2


        //tao playmenu
        playMenu = new Menu(renderer);
        playMenu->addButton("easy", 600, 150, "res/Menu/EasyMode.png", renderer, 0.5, false, true);
        playMenu->addButton("medium", 600, 350, "res/Menu/MediumMode.png", renderer, 0.5, false, true);
        playMenu->addButton("hard", 600, 550, "res/Menu/HardMode.png", renderer, 0.5, false, true);

        //tao m
        mageMenu = new Menu(renderer);
        mageMenu->addButton("d1", 600, 150, "res/Menu/EasyMode.png", renderer, 0.3, false, true);
        mageMenu->addButton("d2", 600, 350, "res/Menu/MediumMode.png", renderer, 0.3, false, true);
        mageMenu->addButton("d3", 600, 550, "res/Menu/HardMode.png", renderer, 0.3, false, true);

        trailMenu = new Menu(renderer);
        trailMenu->addButton("f1", 600, 150, "res/Menu/EasyMode.png", renderer, 0.3, false, true);
        trailMenu->addButton("f2", 600, 350, "res/Menu/MediumMode.png", renderer, 0.3, false, true);
        trailMenu->addButton("f3", 600, 550, "res/Menu/HardMode.png", renderer, 0.3, false, true);
        //playMenu->getPanel()->setH(playMenu->getPanel()->getH() * 1.4);
        //playMenu->getPanel()->setW(playMenu->getPanel()->getW() * 1.4);
        //playMenu->getPanel()->setAC(600,400);

    }




    //tao con tro chuot
    Entity snip = Entity(0, 300, "res/Menu/pointer.png", renderer);
    snip.setScale(0.45);
    snip.render();

    SDL_RenderPresent(renderer);

    SDL_Event ev;

    int FPS = 60;
    int frameDelay = 1000 / FPS;
    int frameTime = 0;

    bool running = true;
    /*
    menuIsOpen:
    0: mainmenu
    1: play
    2: mage
    3: trail
    */
    while(running){
        frameTime = SDL_GetTicks();
        //mainMenu->forceUnHL();
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT) return;
            if(ev.type == SDL_MOUSEMOTION){
                snip.setAC(ev.button.x , ev.button.y);
                mainMenu->checkMouseMove(ev.button.x , ev.button.y);
            }
            if(ev.type == SDL_MOUSEBUTTONDOWN){
                string t1 = mainMenu->checkMouseClick(ev.button.x , ev.button.y);
                     if(t1 == "PlayMenu") menuIsOpen = 1;
                else if(t1 == "MageMenu") menuIsOpen = 2;
                else if(t1 == "TrailMenu") menuIsOpen = 3;
                mainMenu->forceUnHL();
            }

            if(menuIsOpen == 1){ //dang o playmenu
                if(ev.type == SDL_MOUSEMOTION){
                    playMenu->checkMouseMove(ev.button.x , ev.button.y);
                }
                else if(ev.type == SDL_MOUSEBUTTONDOWN){
                    string temp = playMenu->checkMouseClick(ev.button.x , ev.button.y);
                    if(temp == "easy"){
                        menuIsOpen = 0;
                        running = false;
                        newGame(window, renderer, 1);
                    }
                    else if (temp == "medium"){
                        //mo menu settinggame
                    }
                    else if (temp == "hard"){
                        //mo menu guidegame
                    }

                }
                //mainMenu->forceHL(0);
            }
            else if(menuIsOpen == 2){   //dang o magemenu
                if(ev.type == SDL_MOUSEMOTION){
                    playMenu->checkMouseMove(ev.button.x , ev.button.y);

                }
                else if(ev.type == SDL_MOUSEBUTTONDOWN){
                    string temp = playMenu->checkMouseClick(ev.button.x , ev.button.y);
                    if(temp == "d1"){
                        menuIsOpen = 1;
                    }
                    else if (temp == "d2"){
                        //mo menu settinggame
                    }
                    else if (temp == "d3"){
                        //mo menu guidegame
                    }
                }
                //);
            }

        }

        if(!running) break;
        background->render();
        mainMenu->forceHL(menuIsOpen-1);
        mainMenu->render(); //render mainmenu
        if(menuIsOpen == 1){
            playMenu->render(); //render playmenu
        }
        else if(menuIsOpen == 2){
            mageMenu->render(); //render playmenu
        }
        else if(menuIsOpen == 3){
            trailMenu->render(); //render playmenu
        }

        //render con tro
        snip.setAngle(snip.getAngle()+3);
        snip.render();

        SDL_RenderPresent(renderer);

        frameTime = frameDelay - SDL_GetTicks() + frameTime;
        if(frameTime>0) this_thread::sleep_for(chrono::milliseconds(frameTime));
    }

}




