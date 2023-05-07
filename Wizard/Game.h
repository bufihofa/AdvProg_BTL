#pragma once
#include <bits/stdc++.h>
#include <SDL.h>
#include "Animation.h"
using namespace std;
class Spike;
class Bullet;
class Exp;
class Player;
class NPC;
class Grid;
class Game{
private:
    bool running = true;
    bool pause = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    AnimationList* animation;
    vector<Spike*> spike;
    vector<Bullet*> bullet;
    vector<Exp*> exp;

public:
    int diffMode = 0;
    bool levelUpMenuOpen = false;
    Player* p;
    Grid* g;
    Game();
    Game(SDL_Window* window, SDL_Renderer* renderer, AnimationList* animation);

    void renderGrass(SDL_Renderer* renderer, int _dx, int _dy);
    void handleEvents();
    void update();
    void render();
    void levelUpIconRender();
    void timeRender();
    void timeRender2();
    void scoreRender();
    bool isRunning(){ return running; }
    bool isPause(){ return pause; }
    void checkDelay(int& delay);
    void gamePause();
    void gameContinue();
    void createEnemy();
    void createExp();
    void onPlayerDead();
    void onPlayerLevelUp();
    void deadMenuClicked(string name);
    void levelUpMenuClicked(string name);
    void pauseMenuClicked(string name);
    void drawParticle(int _lifeTime, double _pX, double _pY);
    bool checkCollide(NPC* npc);

    vector<Spike*>& getSpikeLoc(){
        return spike;
    }
    vector<Bullet*>& getBulletLoc(){
        return bullet;
    }
    vector<Exp*>& getExpLoc(){
        return exp;
    }
};

