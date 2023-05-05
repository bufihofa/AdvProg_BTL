#include <bits/stdc++.h>
#include "Game.h"
#include "Entity.h"
#include "Npc.h"
#include "QTree.h"
#include "MainMenu.h"
#include "Menu.h"
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
Entity* particlePen = NULL;

vector<SDL_Texture*> grassTile;
Entity* grassPen = NULL;

Grid* grid20 = NULL;
Grid* grid10 = NULL;
Grid* grid5 = NULL;
Player* player = NULL;

int DEAD_ID;
int mouseX, mouseY;


Menu* levelUpMenu = NULL;
vector<string> buttonLU(3);
vector<SDL_Texture*> buttonLV(3);

Entity* XPBar = NULL;
Entity* XPBar2 = NULL;
Entity* HPBar = NULL;
Entity* HPBar2 = NULL;


Mix_Chunk  *expCollectSound = NULL,
           *horrorSound = NULL,
           *levelUpSound = NULL,
           *clickedSound = NULL;

double GameTime = 0;
double SpawnTime = 0;
double SpawnCountTime = 0;

void createLevelUpMenu(SDL_Renderer* renderer){
    levelUpMenu = new Menu(renderer, "res/Menu/PlayMenu.png");
    levelUpMenu->addButton("id_1", 350, 400, "res/Menu/Card X4.png", renderer, 0.55, false, true);
    levelUpMenu->addButton("id_2", 600, 400, "res/Menu/Card X4.png", renderer, 0.55, false, true);
    levelUpMenu->addButton("id_3", 850, 400, "res/Menu/Card X4.png", renderer, 0.55, false, true);

}

void loadGrassTile(int t, SDL_Renderer* renderer){
    string s;
    for(int i = 0; i<=5;++i){
        s = "res/grassTile/"+to_string(t)+"/grassTile_"+to_string(i)+".png";
        grassTile.push_back(loadTexture(s, renderer));
    }

}
void soundLoad(){
    expCollectSound = Mix_LoadWAV("res/wav/exp.wav");
    horrorSound = Mix_LoadWAV("res/wav/horror.wav");
    clickedSound = Mix_LoadWAV("res/wav/click.wav");
    levelUpSound = Mix_LoadWAV("res/wav/levelup.wav");
}
void Game::checkDelay(int& delay){
    if(delay>14){
        if(this->g == grid5){
            this->g == grid10;
        }
        else if(this->g == grid10){
            this->g = grid20;
        }
    }
    else{
        if(this->g == grid20){
            this->g == grid10;
        }
        else if(this->g == grid10){
            this->g = grid5;
        }
    }
}
Game::Game(SDL_Window* window, SDL_Renderer* renderer, AnimationList* animation){
    GameTime = 0;
    this->renderer = renderer;
    this->window = window;
    this->animation = animation;
    if(XPBar == NULL){
        XPBar = new Entity(5, 21, "res/Menu/XP.png", renderer);
        XPBar2 = new Entity(5, 21, "res/Menu/XP_2.png", renderer);
        HPBar = new Entity(5, 5, "res/Menu/HP.png", renderer);
        HPBar2 = new Entity(5, 5, "res/Menu/HP_2.png", renderer);

        XPBar2->setHW(10, 250);
        HPBar2->setHW(15, 300);
        XPBar->setHW(10, 0);
        HPBar->setHW(15, 300);
    }
    if(expCollectSound == NULL){
        soundLoad();
    }
    if(particlePen == NULL){
        particlePen = new Entity(0, 0, "res/Ani/Round_Particle.png", renderer);
    }
    if(grassPen == NULL){
        loadGrassTile(0, renderer);
        grassPen = new Entity(0, 0, grassTile.at(0), renderer);
        grassPen->setHW(320, 320);
    }
    if(levelUpMenu == NULL){
        createLevelUpMenu(renderer);
    }

    player = new Player(100, 100, 4, 0.7, animation, renderer, this);
    this->p = player;

    grid20 = new Grid(-120, -80, 1440, 960, 20, this);
    grid10 = new Grid(-120, -80, 1440, 960, 10, this);
    grid5 = new Grid(-120, -80, 1440, 960, 5, this);
    this->g = grid10;



    DEAD_ID = animation->convertNameToID("Dead");
    startTime = SDL_GetTicks();
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
void Game::levelUpMenuClicked(string name){
    Mix_PlayChannel(-1, clickedSound, 0);
    int t = 3;
    if(name == "id_1"){
        t = 0;
    }
    if(name == "id_2"){
        t = 1;
    }
    if(name == "id_3"){
        t = 2;
    }

    if(t==0 || t==1 || t==2){
        string temp = buttonLU.at(t);
        if(temp == "fireburst"){
            player->upSkill("fireburst");
        }
        else if(temp == "blue"){
            player->upSkill("blue");
        }
        else if(temp == "tornado"){
            player->upSkill("tornado");
        }
        else if(temp == "blast"){
            player->upSkill("blast");
        }
        else if(temp == "lightning"){
            player->upSkill("lightning");
        }
        else if(temp == "lightningO"){
            player->upSkill("lightningO");
        }
        else if(temp == "lightningC"){
            player->upSkill("lightningC");
        }
        levelUpMenuOpen = false;
        gameContinue();

    }
}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(levelUpMenuOpen){
        if(event.type == SDL_MOUSEMOTION){
            levelUpMenu->onMouseMove(event.button.x , event.button.y);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            levelUpMenuClicked(levelUpMenu->getButtonClicked(event.button.x, event.button.y));
        }
        levelUpMenu->render();
        SDL_RenderPresent(renderer);
        return;
    }
    if(event.type == SDL_KEYDOWN){
        if((event.key.keysym.sym == SDLK_a)){
            gamePause();
            openMenu(window, renderer, 1200, 800);
        }
    }
    if(!this->isPause()){
        if(event.type == SDL_MOUSEBUTTONDOWN && player->canAttack()){
            SDL_GetMouseState(&mouseX, &mouseY);
            player->playAttackAnimation(mouseX-600+player->getX(), mouseY-400+player->getY());

        }
        if(event.type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&mouseX, &mouseY);
            if(abs(mouseX-600)<44 && abs(mouseY-400)<44){
                player->vecX = 0;
                player->vecY = 0;
            }
            else player->updateVec(mouseX-600+player->getX(), mouseY-400+player->getY());
            player->setToXY(mouseX-600+player->getX(), mouseY-400+player->getY());
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


    XPBar2->render();
    HPBar2->render();
    XPBar->setW(player->getXPPro()*250);
    HPBar->setW(player->getHPPro()*300);
    XPBar->render();
    HPBar->render();
    SDL_RenderPresent(renderer);


}
void Game::createEnemy(){
    int tempX = player->getX() - 1800 + rand() % 3600;
    int tempY = player->getY() - 1200 + rand() % 2400;
    if(tempX < player->getX() - 666 || tempX > player->getX() + 666 || tempY < player->getY() - 444 || tempY > player->getY() + 444){
        spike.push_back(new Spike("Spike1", 30 + sqrt(GameTime), 30 + sqrt(GameTime), 0.1 + sqrt(GameTime/100000), 2 + (rand()%20)/20, 1 + (rand()%20)/100, tempX, tempY, animation, renderer, this));
    }
    else{
        if(tempX > player->getX()) tempX = tempX + 666 + rand() % 333;
        if(tempX < player->getX()) tempX = tempX - 666 - rand() % 333;
        if(tempY > player->getY()) tempY = tempY + 444 + rand() % 222;
        if(tempY < player->getY()) tempY = tempY - 444 + rand() % 222;
        spike.push_back(new Spike("Spike2", 30 + sqrt(GameTime), 30 + sqrt(GameTime), 0.1 + sqrt(GameTime/100000), 2 + (rand()%20)/20, 1 + (rand()%20)/100, tempX, tempY, animation, renderer, this));
   }
}
void Game::createExp(){
    int tempX = player->getX() - 2200 + rand() % 4200;
    int tempY = player->getY() - 1400 + rand() % 2800;
    int xp = 5 - int(sqrt(sqrt(rand()%256 )));
    if(tempX < player->getX() - 666 || tempX > player->getX() + 666 || tempY < player->getY() - 444 || tempY > player->getY() + 444){
        exp.push_back(new Exp(xp*xp*xp+3, tempX, tempY, renderer, animation));
    }
    else{
        if(tempX > player->getX()) tempX = tempX + 666 + rand() % 333;
        if(tempX < player->getX()) tempX = tempX - 666 - rand() % 333;
        if(tempY > player->getY()) tempY = tempY + 444 + rand() % 222;
        if(tempY < player->getY()) tempY = tempY - 444 + rand() % 222;
        exp.push_back(new Exp(xp*xp*xp+3, tempX, tempY, renderer, animation));
   }
}
void Game::onPlayerDead(){

}
void Game::onPlayerLevelUp(){
    gamePause();
    levelUpMenuOpen = true;
    Mix_PlayChannel(-1, levelUpSound, 0);
    int temp;
    for(int i = 0;i<3;++i){
        temp = rand()%7;
        if(temp == 0){
            buttonLU.at(i) = "fireburst";
        }
        if(temp == 1){
            buttonLU.at(i) = "tornado";
        }
        if(temp == 2){
            buttonLU.at(i) = "blue";
        }
        if(temp == 3){
            buttonLU.at(i) = "blast";
        }
        if(temp == 4){
            buttonLU.at(i) = "lightning";
        }
        if(temp == 5){
            buttonLU.at(i) = "lightningO";
        }
        if(temp == 6){
            buttonLU.at(i) = "lightningC";
        }
        cout<<buttonLU.at(i)<<"\n";
    }
    cout<<"LEVELUP\n";
}
bool cmp(NPC* a1, NPC* a2){
    return a1->distanceBetween(player) < a2->distanceBetween(player);
}
void Game::update(){
    player->update();

    GameTime+=16.67;
    SpawnCountTime+=16.67;
    SpawnTime=66666/sqrt(GameTime);

    while(SpawnCountTime>SpawnTime){
        SpawnCountTime -= SpawnTime;
        if(spike.size()<1000){
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

    g->update(p->getX()-720, p->getY()-480);
    g->hashSkill();

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
                g->findPath(spike.at(i));
            }

        }
    }

    if(exp.size()>0){
        for(int i = 0;i<exp.size();++i){
            if(exp.at(i)->check(player->getX(), player->getY(), 130)){
                if(exp.at(i)->getXP() > 0){
                    player->addXP(exp.at(i)->getXP());
                    Mix_PlayChannel(-1, expCollectSound, 0);
                }
                exp.erase(exp.begin() + i);
                i--;
            }
        }
    }
    //


}

