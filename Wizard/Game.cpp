#include <bits/stdc++.h>
#include "Game.h"
#include "Entity.h"
#include "Npc.h"
#include "QTree.h"
double startTime = 0;

class Ptc{
public:
    int tempL = 0;
    int lifetime;
    double x, y;
    Ptc(int _lifetime, double _x, double _y){
        lifetime = _lifetime;
        x = _x;
        y = _y;
    }
    void nextLife(){
        tempL++;
        if(tempL == 3){
            tempL = 0;
            lifetime--;
        }
    }
};
vector<Ptc*> Particles;
Entity* particlePen;

vector<SDL_Texture*> grassTile;
Entity* grassPen;

Grid* grid;
Player* player;

int DEAD_ID;
int mouseX, mouseY;

void loadGrassTile(int t, SDL_Renderer* renderer){
    string s;
    for(int i = 0; i<=5;++i){
        s = "res/grassTile/"+to_string(t)+"/grassTile_"+to_string(i)+".png";
        grassTile.push_back(loadTexture(s, renderer));
    }

}
Game::Game(SDL_Window* window, SDL_Renderer* renderer, AnimationList* animation){
    particlePen = new Entity(0, 0, "res/Ani/Round_Particle.png", renderer);
    particlePen->setHW(1, 1);
    DEAD_ID = animation->convertNameToID("Dead");
    this->renderer = renderer;
    this->window = window;
    this->animation = animation;
    player = new Player(100, 100, 4, 0.7, animation, renderer, this);
    this->p = player;

    //load grass texture
    loadGrassTile(rand()%2, renderer);

    grassPen = new Entity(0, 0, grassTile.at(0), renderer);
    grassPen->setHW(320, 320);
    startTime = SDL_GetTicks();


    grid = new Grid(-120, -80, 1440, 960, 20, this);
    this->g = grid;
    cout<<"LOG: Create Game OK\n";
}

void Game::renderGrass(SDL_Renderer* renderer, int _dx, int _dy){

    int dx = int(player->getX()/320);
    int dy = int(player->getY()/320);
    for(int i = dx-4; i < dx+5; ++i){
        for(int j = dy-3; j < dy+4; ++j){
            grassPen->setImage(grassTile.at(abs((i+j)%6)));
            grassPen->setXY(i*320 - _dx, j*320 - _dy);
            grassPen->render();
        }
    }

}
/*

*/
void Game::gamePause(){
    this->pause = true;
    //pauseButton.setImage(loadTexture("resources/Play_BTN.png", this->renderer));
    //pausetext.render();
}
void Game::gameContinue(){
    //pauseButton.setImage(loadTexture("resources/Pause_BTN.png", this->renderer));
    this->pause = false;
}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_KEYDOWN){
        if((event.key.keysym.sym == SDLK_a)){
            if(isPause()) gameContinue();
            else{
                gamePause();
                grid->printMap();
            }
        }
    }

    if(!this->isPause()){
        if(event.type == SDL_MOUSEBUTTONDOWN && player->canAttack()){
            player->playAttackAnimation();

        }
        if(event.type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&mouseX, &mouseY);
            if(abs(mouseX-600)<44 && abs(mouseY-400)<44){
                player->vecX = 0;
                player->vecY = 0;
            }
            else player->updateVec(mouseX-600+player->getX(), mouseY-400+player->getY());
        }

    }
}
void Game::drawParticle(int _lifeTime, double _pX, double _pY){
    Particles.push_back(new Ptc(_lifeTime, _pX, _pY));
}
void Game::render(){
    double dx = player->getX() - 600; // camera x
    double dy = player->getY() - 400; // camera

    // draw grass
    this->renderGrass(renderer, dx ,dy);
    if(Particles.size()>0){
        for(int i = 0;i<Particles.size();++i){
            if(Particles.at(i)->lifetime == 0){
                Particles.erase(Particles.begin() + i);
                i--;
            }
            else{
                particlePen->setHW(1+Particles.at(i)->lifetime, 1+Particles.at(i)->lifetime);
                particlePen->setXY(Particles.at(i)->x, Particles.at(i)->y);
                particlePen->renderCenter_Cam(dx, dy);
                Particles.at(i)->nextLife();
            }
        }
    }
    if(exp.size()>0){
        for(int i = 0;i<exp.size();++i){
            exp.at(i)->renderCenter_Cam(dx, dy);

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


    player->renderNPC(dx, dy);

    SDL_RenderPresent(renderer);


}
void Game::createEnemy(){
    int tempX = player->getX() - 1800 + rand() % 3600;
    int tempY = player->getY() - 1200 + rand() % 2400;
    if(tempX < player->getX() - 666 || tempX > player->getX() + 666 || tempY < player->getY() - 444 || tempY > player->getY() + 444){
        spike.push_back(new Spike("Spike1", 100, 100, 2 + (rand()%20)/20, 1 + (rand()%20)/100, tempX, tempY, animation, renderer, this));
    }
    else{
        if(tempX > player->getX()) tempX = tempX + 666 + rand() % 333;
        if(tempX < player->getX()) tempX = tempX - 666 - rand() % 333;
        if(tempY > player->getY()) tempY = tempY + 444 + rand() % 222;
        if(tempY < player->getY()) tempY = tempY - 444 + rand() % 222;
        spike.push_back(new Spike("Spike2", 100, 100, 2 + (rand()%20)/20, 1 + (rand()%20)/100, tempX, tempY, animation, renderer, this));
   }
}
void Game::createExp(){
    int tempX = player->getX() - 2200 + rand() % 4200;
    int tempY = player->getY() - 1400 + rand() % 2800;
    int xp = 5 - int(sqrt(sqrt(rand()%256 )));
    if(tempX < player->getX() - 666 || tempX > player->getX() + 666 || tempY < player->getY() - 444 || tempY > player->getY() + 444){
        exp.push_back(new Exp(xp*xp*xp, tempX, tempY, renderer, animation));
    }
    else{
        if(tempX > player->getX()) tempX = tempX + 666 + rand() % 333;
        if(tempX < player->getX()) tempX = tempX - 666 - rand() % 333;
        if(tempY > player->getY()) tempY = tempY + 444 + rand() % 222;
        if(tempY < player->getY()) tempY = tempY - 444 + rand() % 222;
        exp.push_back(new Exp(xp*xp*xp, tempX, tempY, renderer, animation));
   }
}

void Game::onPlayerLevelUp(){
    gamePause();

}
bool cmp(NPC* a1, NPC* a2){
    return a1->distanceBetween(player) < a2->distanceBetween(player);
}
void Game::update(){
    if(spike.size()<1000){
        if(rand()%50 >45){
            createEnemy();
        }
    }

    sort(spike.begin(), spike.end(), cmp);


    if(bullet.size()>0){
        for(int i = 0;i<bullet.size();++i){
            bullet.at(i)->update(16.67);
            if(bullet.at(i)->skillStatus == -1){

                bullet.erase(bullet.begin() + i);
                i--;
            }
        }
    }
    player->update();
    grid->update(p->getX()-720, p->getY()-480);
    grid->hashSkill();

    if(spike.size()>0){
        for(int i = 0;i<spike.size();++i){
            if(spike.at(i)->isDead()){
                spike.at(i)->setHW(100, 100);
                spike.at(i)->deadAnimation++;
                spike.at(i)->setImage(animation->getAnimationWithID(DEAD_ID, (spike.at(i)->deadAnimation) /4));

                if(spike.at(i)->deadAnimation == 28){
                    spike.erase(spike.begin() + i);
                }
            }
            else{
                grid->findPath(spike.at(i));
            }

        }
    }

    if(exp.size()>0){
        for(int i = 0;i<exp.size();++i){
            if(exp.at(i)->check(player->getX()+20, player->getY(), 130)){
                if(exp.at(i)->getXP() > 0){
                    player->addXP(exp.at(i)->getXP());
                }
                exp.erase(exp.begin() + i);
                i--;
            }
        }
    }
    //


}

