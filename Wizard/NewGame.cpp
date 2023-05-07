
#include "NewGame.h"
#include "Game.h"
#include <thread>
#include <chrono>
using namespace std;

Game* game = NULL;
AnimationList* animation = NULL;
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
    animation = new AnimationList();
    animation->loadAnimation("Dead", "res/Ani/Dead/Dead_", 8, 20, renderer);
    animation->loadAnimation("WizIdle", "res/Ani/Wiz/Idle_", 6, 60, renderer);
    animation->loadAnimation("WizDead", "res/Ani/Wiz/Dead_", 7, 60, renderer);
    animation->loadAnimation("WizAttack", "res/Ani/Wiz/Attack_", 8, 60, renderer);
    animation->loadAnimation("WizAttack2", "res/Ani/Wiz/Atack2_", 8, 60, renderer);
    animation->loadAnimation("WizRun", "res/Ani/Wiz/Run_", 8, 60, renderer);
    animation->loadAnimation("Spike1", "res/Ani/Spike/Spike1_", 9, 60, renderer);
    animation->loadAnimation("Spike2", "res/Ani/Spike/Spike2_", 9, 60, renderer);
    animation->loadAnimation("Spike3", "res/Ani/Spike/Spike3_", 8, 60, renderer);
    animation->loadAnimation("Spike4", "res/Ani/Spike/Spike4_", 8, 60, renderer);
    animation->loadAnimation("RedSpike1", "res/Ani/Spike/RedSpike1_", 8, 60, renderer);
    animation->loadAnimation("RedSpike2", "res/Ani/Spike/RedSpike2_", 8, 60, renderer);

    animation->loadAnimation("Exp", "res/Ani/Exp/Exp_", 4, 20, renderer);

    animation->loadAnimation("Burst1", "res/Ani/Skill/Burst1/BE_", 27, 20, renderer);
    animation->loadAnimation("Tornado", "res/Ani/Skill/Tornado/Tornado_", 25, 20, renderer);
    animation->loadAnimation("Blue", "res/Ani/Skill/Blue/Blue_", 30, 20, renderer);
    animation->loadAnimation("Purple", "res/Ani/Skill/Purple/Purple_", 20, 20, renderer);
    animation->loadAnimation("Blast", "res/Ani/Skill/Blast/Blast_", 10, 20, renderer);
    animation->loadAnimation("Lightning", "res/Ani/Skill/Lightning/Lightning_", 7, 20, renderer);
    animation->loadAnimation("LightningC", "res/Ani/Skill/LightningC/LightningC_", 11, 20, renderer);
    animation->loadAnimation("LightningO", "res/Ani/Skill/LightningO/LightningO_", 20, 20, renderer);
}
void newGame(SDL_Window* window, SDL_Renderer* renderer, int diffMode){

    if(animation == NULL) loadResources(renderer);

    game = new Game(window, renderer, animation);
    game->diffMode = diffMode;
    double UPS = 60;
    double updateDelay = 1000 / UPS;
    int updateTime = 0;
    int delay;
    while(game->isRunning()){
        updateTime = SDL_GetTicks();
        game->handleEvents();
        if(!game->isPause()){
            game->handleEvents();
            game->handleEvents();
            game->handleEvents();
            game->handleEvents();
            game->update();
            game->render();
        }
        delay = SDL_GetTicks() - updateTime;
        game->checkDelay(delay);
        updateTime = updateDelay - SDL_GetTicks() + updateTime;
        if(updateTime>0){
            this_thread::sleep_for(chrono::milliseconds(updateTime));
        }
    }
}
