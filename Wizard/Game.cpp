#include <bits/stdc++.h>
#include "Game.h"
#include "Entity.h"
#include "Npc.h"
#include "Grid.h"
#include "MainMenu.h"
#include "Menu.h"
#include "NewGame.h"
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

Entity* redborder = NULL;

Grid* grid20 = NULL;
Grid* grid10 = NULL;
Grid* grid5 = NULL;
Player* player = NULL;

int DEAD_ID;
int mouseX, mouseY;


Menu* levelUpMenu = NULL;
Menu* pauseMenu = NULL;
Menu* deadMenu = NULL;

vector<string> buttonLU(3);

Entity* XPBar = NULL;
Entity* XPBar2 = NULL;
Entity* HPBar = NULL;
Entity* HPBar2 = NULL;

vector<SDL_Texture*> number;
vector<SDL_Texture*> skillIcon;
Entity* skillPen = NULL;
Entity* numberPen = NULL;
Mix_Chunk  *expCollectSound = NULL,
           *horrorSound = NULL,
           *hittedSound = NULL,
           *levelUpSound = NULL,
           *clickedSound = NULL;

double GameTime = 0;
double SpawnTime = 0;
double SpawnCountTime = 0;
int score;
int second;
int giay1;
int giay2;
int phut1;
int phut2;
bool PauseMenu;

void createLevelUpMenu(SDL_Renderer* renderer){
    levelUpMenu = new Menu(renderer, "res/Menu/PlayMenu.png");
    levelUpMenu->getPanel()->setH(400);
    levelUpMenu->addButton("id_1", 350, 430, "res/Menu/Card X4.png", renderer, 0.55, true);
    levelUpMenu->addButton("id_2", 600, 430, "res/Menu/Card X4.png", renderer, 0.55, true);
    levelUpMenu->addButton("id_3", 850, 430, "res/Menu/Card X4.png", renderer, 0.55, true);

    deadMenu = new Menu(renderer, "res/Menu/DeadPanel.png");
    deadMenu->addButton("1", 450, 550, "res/Menu/RestartButton.png", renderer, 0.55, true);
    deadMenu->addButton("2", 750, 550, "res/Menu/MenuButton.png", renderer, 0.55, true);

    pauseMenu = new Menu(renderer, "res/Menu/PausePanel.png");
    pauseMenu->addButton("1", 400, 550, "res/Menu/RestartButton.png", renderer, 0.55, true);
    pauseMenu->addButton("2", 800, 550, "res/Menu/MenuButton.png", renderer, 0.55, true);
    pauseMenu->addButton("3", 600, 550, "res/Menu/ResumeButton.png", renderer, 0.55, true);
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
    hittedSound = Mix_LoadWAV("res/wav/hit.wav");
}
void Game::checkDelay(int& delay){
    //cout<<delay<<"\n";
}
void Game::timeRender(){
    numberPen->setHW(30, 25);
    numberPen->setXY(560, 20);
    numberPen->setImage(number.at(phut1));
    numberPen->render();
    numberPen->setXY(575, 20);
    numberPen->setImage(number.at(phut2));
    numberPen->render();
    numberPen->setXY(585, 23);
    numberPen->setImage(number.at(10));
    numberPen->render();
    numberPen->setXY(595, 20);
    numberPen->setImage(number.at(giay1));
    numberPen->render();
    numberPen->setXY(610, 20);
    numberPen->setImage(number.at(giay2));
    numberPen->render();
}
void Game::timeRender2(){
    numberPen->setHW(70, 60);
    numberPen->setXY(540, 305);
    numberPen->setImage(number.at(phut1));
    numberPen->render();
    numberPen->setXY(575, 305);
    numberPen->setImage(number.at(phut2));
    numberPen->render();
    numberPen->setXY(600, 313);
    numberPen->setImage(number.at(10));
    numberPen->render();
    numberPen->setXY(625, 305);
    numberPen->setImage(number.at(giay1));
    numberPen->render();
    numberPen->setXY(660, 305);
    numberPen->setImage(number.at(giay2));
    numberPen->render();
}
void Game::scoreRender(){
    int dx = 560;
    int dy = 380;
    string s = to_string(score);
    for(int i = 0; i<s.size(); ++i){
        numberPen->setXY(dx, dy);
        numberPen->setImage(number.at(s[i]-48));
        numberPen->render();
        dx+=35;
    }
}
Game::Game(SDL_Window* window, SDL_Renderer* renderer, AnimationList* animation){
    GameTime = 0;
    SpawnTime = 0;
    SpawnCountTime = 0;
    this->renderer = renderer;
    this->window = window;
    this->animation = animation;
    if(number.size()==0){
        for(int i = 0; i <= 9; ++i){
            number.push_back(loadTexture("res/number/"+to_string(i)+".png", renderer));
        }
        number.push_back(loadTexture("res/number/haicham.png", renderer));
        numberPen = new Entity(0, 0, number.at(0), renderer);
        numberPen->setHW(30, 25);

        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/purple.png", renderer));//0
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/blast.png", renderer));//1
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/blue.png", renderer));//2
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/fireburst.png", renderer));//3
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/lightning.png", renderer));//4
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/lightningO.png", renderer));//5
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/lightningC.png", renderer));//6
        skillIcon.push_back(loadTexture("res/Ani/Skill/Icon/tornado.png", renderer));//7
        skillPen = new Entity(0, 0, skillIcon.at(0), renderer);
    }
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
        redborder = new Entity(0, 0, "res/redborder.png", renderer);
        redborder->setHW(800, 1200);
    }
    if(grassPen == NULL){
        loadGrassTile(0, renderer);
        grassPen = new Entity(0, 0, grassTile.at(0), renderer);
        grassPen->setHW(320, 320);
    }
    if(levelUpMenu == NULL){
        createLevelUpMenu(renderer);
    }

    player = new Player(200, 200, 4, 0.7, animation, renderer, this);
    this->p = player;

    grid20 = new Grid(-300, -200, 1800, 1200, 20, this);
    grid10 = new Grid(-300, -200, 1800, 1200, 20, this);
    grid5 = new Grid(-300, -200, 1800, 1200, 20, this);
    this->g = grid10;



    DEAD_ID = animation->convertNameToID("Dead");
    startTime = SDL_GetTicks();
    cout<<"LOG: Create Game OK\n";
    score = 0;
    PauseMenu = false;
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
}
void Game::gameContinue(){
    this->pause = false;
}
void Game::deadMenuClicked(string name){
    Mix_PlayChannel(-1, clickedSound, 0);
    if(name=="1"){
        running = false;
        newGame(window, renderer, diffMode);
    }
    if(name=="2"){
        running = false;
        openMenu(window, renderer, 1200, 800);
    }
}
void Game::pauseMenuClicked(string name){
    Mix_PlayChannel(-1, clickedSound, 0);
    if(name=="1"){
        running = false;
        newGame(window, renderer, diffMode);
    }
    if(name=="2"){
        running = false;
        openMenu(window, renderer, 1200, 800);
    }
    if(name=="3"){
        PauseMenu = false;
        gameContinue();
    }
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
void Game::levelUpIconRender(){
    string temp;
    skillPen->setXY(350, 430);
    for(int i = 0; i < 3; ++i){
        temp = buttonLU.at(i);
        if(temp == "fireburst"){
            skillPen->setImage(skillIcon.at(3));
            skillPen->setHW(130, 130);
        }
        else if(temp == "blue"){
            skillPen->setImage(skillIcon.at(2));
            skillPen->setHW(130, 130);
        }
        else if(temp == "tornado"){
            skillPen->setImage(skillIcon.at(7));
            skillPen->setHW(160, 160);
        }
        else if(temp == "blast"){
            skillPen->setImage(skillIcon.at(1));
            skillPen->setHW(130, 130);
        }
        else if(temp == "lightning"){
            skillPen->setImage(skillIcon.at(4));
            skillPen->setHW(140, 70);
        }
        else if(temp == "lightningO"){
            skillPen->setImage(skillIcon.at(5));
            skillPen->setHW(100, 100);
        }
        else if(temp == "lightningC"){
            skillPen->setImage(skillIcon.at(6));
            skillPen->setHW(100, 100);
        }
        if(levelUpMenu->getButton(i)->isHighLight()) skillPen->setScale(1.15);
        skillPen->renderCenter();
        skillPen->addX(250);
    }

}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(player->deadFrame==120){
        gamePause();
        if(event.type == SDL_MOUSEMOTION){
            deadMenu->onMouseMove(event.button.x , event.button.y);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            deadMenuClicked(deadMenu->getButtonClicked(event.button.x, event.button.y));
        }
        if(!running){
            return;
        }
        deadMenu->render();
        timeRender2();
        scoreRender();
        SDL_RenderPresent(renderer);
    }
    if(levelUpMenuOpen){
        if(event.type == SDL_MOUSEMOTION){
            levelUpMenu->onMouseMove(event.button.x , event.button.y);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            levelUpMenuClicked(levelUpMenu->getButtonClicked(event.button.x, event.button.y));
        }
        if(!running){
            return;
        }
        levelUpMenu->render();
        levelUpIconRender();
        SDL_RenderPresent(renderer);
        return;
    }
    if(!running){
        return;
    }
    if(event.type == SDL_KEYDOWN){
        if((event.key.keysym.sym == SDLK_ESCAPE)){
            gamePause();
            PauseMenu = true;
        }
    }
    if(PauseMenu){
        if(event.type == SDL_MOUSEMOTION){
            pauseMenu->onMouseMove(event.button.x , event.button.y);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            pauseMenuClicked(pauseMenu->getButtonClicked(event.button.x, event.button.y));
        }
        pauseMenu->render();
        timeRender2();
        scoreRender();
        SDL_RenderPresent(renderer);
        return;
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
    if(player->deadFrame==120){
        return;
    }
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
    if(player->hitCount>0){
        for(int i = 0;i <= 1+player->hitCount/10; ++i){
            redborder->render();
        }
        player->hitCount--;
    }
    if(p->isHitted && !p->isDead()){
        p->isHitted = false;
        if(p->hitSoundCount==0){
            Mix_PlayChannel(-1, hittedSound, 0);
            p->hitSoundCount=10;
        }
        else p->hitSoundCount--;
    }
    timeRender();
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
        spike.push_back(new Spike("Spike1", 30 + sqrt(GameTime*diffMode), 30 + sqrt(GameTime*diffMode), 0.1 + sqrt(GameTime/100000*diffMode), 2.3 + diffMode/7.0, 1 + (diffMode-1)/5.0, tempX, tempY, animation, renderer, this));
    }
    else{
        if(tempX > player->getX()) tempX = tempX + 666 + rand() % 333;
        if(tempX < player->getX()) tempX = tempX - 666 - rand() % 333;
        if(tempY > player->getY()) tempY = tempY + 444 + rand() % 222;
        if(tempY < player->getY()) tempY = tempY - 444 + rand() % 222;
        spike.push_back(new Spike("Spike2", 30 + sqrt(GameTime*diffMode), 30 + sqrt(GameTime*diffMode), 0.1 + sqrt(GameTime/100000*diffMode), 2.3 + diffMode/7.0, 1 + (diffMode-1)/5.0, tempX, tempY, animation, renderer, this));
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
    Mix_PlayChannel(-1, horrorSound, 0);
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
    if(player->deadFrame==120){
        player->hitCount=200;
        return;
    }
    player->update();

    GameTime+=16.67;
    SpawnCountTime+=16.67;
    SpawnTime=66666/sqrt(5000+GameTime)/diffMode;

    second = GameTime/1000;
    phut2 = second/60;
    giay2 = second-phut2*60;
    phut1 = phut2/10;
    phut2 = phut2%10;
    giay1 = giay2/10;
    giay2 = giay2%10;
    if(second>3600){
        phut1=9;
        phut2=9;
        giay1=9;
        giay2=9;
    }
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

    g->update(p->getX()-900, p->getY()-600);
    g->hashSkill();

    if(spike.size()>0){
        for(int i = 0;i<spike.size();++i){
            if(spike.at(i)->isDead()){
                spike.at(i)->setHW(100, 100);
                spike.at(i)->deadAnimation++;
                spike.at(i)->setImage(animation->getAnimationWithID(DEAD_ID, (spike.at(i)->deadAnimation) /4));
                if(spike.at(i)->deadAnimation == 28){
                    spike.erase(spike.begin() + i);
                    score++;
                }
            }
            else{
                g->findPath(spike.at(i));
            }

        }
    }
    if(g->hg==1){
        g->hg = 0;
        g->printMap();
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

