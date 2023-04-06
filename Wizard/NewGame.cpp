#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"
#include "Game.h"
#include "NewGame.h"
#include "Animation.h"
#include <thread>
#include <chrono>
using namespace std;

Game* game;
AnimationObject* animation;
/*
void renderThreadFunc(){

    int FPS = 60;
    int frameDelay = 1000 / FPS;
    while(game->isRunning()){
        if(!game->isPause()){
            game->render();
        }
        this_thread::sleep_for(chrono::milliseconds(frameDelay));
    }
}
*/
void loadResources(SDL_Renderer* renderer){
    animation = new AnimationObject();
    animation->loadAnimation("WizIdle", "res/Ani/Wiz/Idle_", 6, 60, renderer);
    animation->loadAnimation("WizAttack", "res/Ani/Wiz/Attack_", 8, 60, renderer);
    animation->loadAnimation("WizAttack2", "res/Ani/Wiz/Atack2_", 8, 60, renderer);
    animation->loadAnimation("WizRun", "res/Ani/Wiz/Run_", 8, 60, renderer);
    animation->loadAnimation("Ene1Attack", "res/Ani/Ene1/Attack_", 8, 60, renderer);
    animation->loadAnimation("Ene1Run", "res/Ani/Ene1/Run_", 6, 60, renderer);
    animation->loadAnimation("Ene1Hitted", "res/Ani/Ene1/Hitted_", 4, 60, renderer);
    animation->loadAnimation("Spike1", "res/Ani/Spike/Spike1_", 8, 60, renderer);
    animation->loadAnimation("Spike2", "res/Ani/Spike/Spike2_", 8, 60, renderer);
    animation->loadAnimation("Spike3", "res/Ani/Spike/Spike3_", 8, 60, renderer);
    animation->loadAnimation("Spike4", "res/Ani/Spike/Spike4_", 8, 60, renderer);
    animation->loadAnimation("RedSpike1", "res/Ani/Spike/RedSpike1_", 8, 60, renderer);
    animation->loadAnimation("RedSpike2", "res/Ani/Spike/RedSpike2_", 8, 60, renderer);
    animation->loadAnimation("Electric", "res/Ani/Skill/Electric/Electric_", 16, 200, renderer);
    animation->loadAnimation("Lightning", "res/Ani/Skill/Lightning/Lightning_", 5, 20, renderer);
}
void newGame(SDL_Window* window, SDL_Renderer* renderer, int diffMode){

    if(animation == NULL) loadResources(renderer);

    game = new Game(window, renderer, animation);

    int UPS = 60;
    int updateDelay = 1000 / UPS;
    int updateTime = 0;
    while(game->isRunning()){
        updateTime = SDL_GetTicks();
        game->handleEvents(); //khi game pause van can bat su kien: vd click cac button

        if(!game->isPause()){
            //goi bat su kien nhieu de ko bi delay: vi du an lien tiep 5 phim 1 lan thi se co nhieu su kien phai cho`
            game->handleEvents();
            game->handleEvents();
            game->handleEvents();
            game->handleEvents();
            game->update();
            game->render();
        }
        //tinh toan de co dinh UPS
        updateTime = updateDelay - SDL_GetTicks() + updateTime;
        if(updateTime>0){
            this_thread::sleep_for(chrono::milliseconds(updateTime));
        }
    }
}
