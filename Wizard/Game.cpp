
#include "Npc.h"
#include "Animation.h"
#include "Entity.h"
#include "Game.h"
#include <bits/stdc++.h>
//using namespace std;
SDL_Window* afd;

double startTime = 0;

Player* player;

deque<SDL_Texture*> grassTile;
Entity* grassPen;



int mouseX, mouseY;
Game::Game(SDL_Window* window, SDL_Renderer* renderer, AnimationObject* animation){
    this->renderer = renderer;
    this->window = window;
    this->animation = animation;
    player = new Player(100, 100, 4, 1, animation, renderer, this);

    //load grass texture
    grassTile.push_back(loadTexture("res/grassTile/grassTile_0.png", renderer));
    grassTile.push_back(loadTexture("res/grassTile/grassTile_1.png", renderer));
    grassTile.push_back(loadTexture("res/grassTile/grassTile_2.png", renderer));
    grassTile.push_back(loadTexture("res/grassTile/grassTile_3.png", renderer));
    grassTile.push_back(loadTexture("res/grassTile/grassTile_4.png", renderer));
    grassTile.push_back(loadTexture("res/grassTile/grassTile_5.png", renderer));

    // su dung grassPen nhu 1 but ve cac grassTile (do co nhieu grassTile)
    grassPen = new Entity(0, 0, grassTile.at(0), renderer);
    grassPen->setHW(320, 320);
    startTime = SDL_GetTicks();

}
void Game::renderGrass(SDL_Renderer* renderer, int _dx, int _dy){
    //lam tron lai cac toa do grassTile de co dinh map
    int dx = int(player->getX()/320);
    int dy = int(player->getY()/320);

    int temp;
    for(int i = dx-4; i < dx+5; ++i){
        for(int j = dy-3; j < dy+4; ++j){
            //moi grassTile co 1 texture khac nhau
            temp = (i+j)%6;
            if(temp<grassTile.size()) grassPen->setImage(grassTile.at(temp));
            //chinh vi tri cua pen de ve
            grassPen->setXY(i*grassPen->getW()-_dx, j*grassPen->getH()-_dy);
            grassPen->render();
        }
    }

}
/*

*/
void Game::gamePause(){
    this->pau();
    //pauseButton.setImage(loadTexture("resources/Play_BTN.png", this->renderer));
    //pausetext.render();
}
void Game::gameContinue(){
    //pauseButton.setImage(loadTexture("resources/Pause_BTN.png", this->renderer));
    this->conti();
}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);

    if(!this->isPause()){
        if(event.type == SDL_MOUSEBUTTONDOWN && player->canAttack()){
            player->playAttackAnimation();

        }
        if(event.type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&mouseX, &mouseY);
            player->updateDirect(mouseX, mouseY);
        }

    }
}
void Game::render(){

    //nhan vat luon o giua man hinh -> camera phai di chuyen theo nhan vat
    //dx va dy la toa do dinh? goc tren ben trai cua camera
    double dx = player->getX() - 600; // camera x
    double dy = player->getY() - 400; // camera y
    // -> truoc khi render ra NPC thi phai tru di toa do cua camera
    // * trong ham render da co -dx va -dy

    // draw grass
    this->renderGrass(renderer, dx ,dy);

    //neu so luong enemy>0 thi render
    if(enemy.size()>0){
        for(int i = 0;i<enemy.size();++i){
            enemy.at(i)->renderNPC(dx, dy);
        }
    }
    if(spike.size()>0){
        for(int i = 0;i<spike.size();++i){
            spike.at(i)->renderNPC(dx, dy);
        }
    }
    if(bullet.size()>0){
        for(int i = 0;i<bullet.size();++i){
            bullet.at(i)->renderNPC(dx, dy);
        }
    }

    //render player
    player->renderNPC(dx, dy);
    SDL_RenderPresent(renderer);
}

void Game::update(){

    if(SDL_GetTicks() % 500 == 11) enemy.push_back(new Enemy("Ene1", 100, 100, 2.8, 1.2, player->getX()-400+SDL_GetTicks() % 400, player->getY()-600, player->getAnima(), player->getRenderer()));
    if(SDL_GetTicks() % 500 == 22) enemy.push_back(new Enemy("Ene1", 100, 100, 2.8, 1.2, player->getX()-400+SDL_GetTicks() % 400, player->getY()-600, player->getAnima(), player->getRenderer()));
    if(SDL_GetTicks() % 500 == 33) enemy.push_back(new Enemy("Ene1", 200, 200, 2.2, 1.5, player->getX()-400+SDL_GetTicks() % 400, player->getY()-600, player->getAnima(), player->getRenderer()));
    if(SDL_GetTicks() % 500 == 44) enemy.push_back(new Enemy("Ene1", 300, 300, 2.0, 2, player->getX()-400+SDL_GetTicks() % 400, player->getY()-600, player->getAnima(), player->getRenderer()));

    player->update();

    //update dich den cho cac enemy la vi tri hien tai cua player
    if(spike.size()>0){
        for(int i = 0;i<spike.size();++i){
            spike.at(i)->setToXY(player->getX(), player->getY());
            spike.at(i)->update();
        }
    }
    if(enemy.size()>0){
        for(int i = 0;i<enemy.size();++i){
            enemy.at(i)->setToXY(player->getX(), player->getY());
            enemy.at(i)->update();
        }
    }
    if(bullet.size()>0){
        for(int i = 0;i<bullet.size();++i){
            bullet.at(i)->update(16.67);
        }
    }
}

