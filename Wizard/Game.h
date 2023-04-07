#ifndef GAME__H
#define GAME__H

#include <SDL.h>
#include "Animation.h"
class Enemy;
class Spike;
class Bullet;

class Game{
private:
    bool running = true;
    bool pause = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    AnimationList* animation;
    vector<Enemy*> enemy;
    vector<Spike*> spike;
    vector<Bullet*> bullet;
public:
    Game();
    Game(SDL_Window* window, SDL_Renderer* renderer, AnimationList* animation);

    void init(const char* title, int x, int y, int h, int w);
    void renderGrass(SDL_Renderer* renderer, int _dx, int _dy);
    void handleEvents();
    void update();
    void render();

    bool isRunning(){ return running; }
    bool isPause(){ return pause; }

    void gamePause();
    void gameContinue();

    vector<Enemy*>& getEnemyLoc(){
        return enemy;
    }
    vector<Spike*>& getSpikeLoc(){
        return spike;
    }
    vector<Bullet*>& getBulletLoc(){
        return bullet;
    }

};


#endif // GAME__H
