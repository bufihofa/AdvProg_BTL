#include "Npc.h"
#include "Game.h"
#include "Grid.h"

Mix_Chunk  *hitSound = NULL,
           *boom0Sound = NULL,
           *boom1Sound = NULL,
           *boom2Sound = NULL,
           *clickSound = NULL,
           *blastSound = NULL,
           *lightning1 = NULL,
           *lightning2 = NULL,
           *lightning3 = NULL,
           *tornadoSound = NULL,
           *purpleSound = NULL,
           *footstep = NULL,
           *fireBurstSound = NULL;
void soundLoad2(){
    hitSound = Mix_LoadWAV("res/wav/hit.wav");
    boom0Sound = Mix_LoadWAV("res/wav/bom_0.wav");
    boom1Sound = Mix_LoadWAV("res/wav/bom_1.wav");
    boom2Sound = Mix_LoadWAV("res/wav/bom_2.wav");
    clickSound = Mix_LoadWAV("res/wav/click.wav");
    lightning1 = Mix_LoadWAV("res/wav/lightning1.wav");
    lightning2 = Mix_LoadWAV("res/wav/lightning2.wav");
    lightning3 = Mix_LoadWAV("res/wav/lightning3.wav");
    fireBurstSound = Mix_LoadWAV("res/wav/firehit.wav");
    tornadoSound = Mix_LoadWAV("res/wav/tornado.wav");
    purpleSound = Mix_LoadWAV("res/wav/purple.wav");
    blastSound = Mix_LoadWAV("res/wav/blast.wav");
    footstep = Mix_LoadWAV("res/wav/footstep.wav");
}
Player::Player(double hp, double maxHP, double speed, double scale, AnimationList* animation, SDL_Renderer* renderer, Game* game){
    this->game = game;
    maxAttackFrame = 8;
    maxIdleFrame = 6;
    maxRunFrame = 8;

    setImage(animation->getAnimation("WizIdle", 0));
    SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);

    setHW(getPos().h, getPos().w);
    setXY(0, 0);
    setScale(scale);
    setHP(hp);
    setMaxHP(maxHP);
    setSpeed(speed);
    setAnimationList(animation);
    setRenderer(renderer);
    isEnemy = false;

    if(hitSound == NULL){
        soundLoad2();
    }
}

void Player::playAttackAnimation(double x, double y){
    if(canAttack()){
        setRun(false);
        setAttack(false);
        attackFrame = -1;
        clickedX = x;
        clickedY = y;
    }
}
void Player::castSkill(string name, int level, double Sx, double Sy){
    int enemyAt = 0;
    if(name == "fireburst"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                Mix_PlayChannel(-1, fireBurstSound, 0);
                for(int i = 0;i <int(2+level*1.5); ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Bullet* b = new Bullet("Burst1", getX(), getY(), 0.5, 1, 12, true, getRenderer(), getAnimationList(), game);
                        b->victim = game->getSpikeLoc().at(enemyAt);
                        b->setAttackDamage(50+level*30);
                        b->r = 1;
                        b->skillType = 0;
                        b->hasParticle = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "tornado"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level/2; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Mix_PlayChannel(-1, tornadoSound, 0);
                        Bullet* b = new Bullet("Tornado", getX(), getY(), 1, 1.5, 15, true, getRenderer(), getAnimationList(), game);
                        b->victim = game->getSpikeLoc().at(i%t);
                        b->setAttackDamage(1+level/2);
                        b->setHW(180, 180);
                        b->r = 60;
                        b->skillType = 1;
                        b->maxTime = 5000+level*500;
                        b->canDodge = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "blue"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level/2; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Bullet* b = new Bullet("Blue", game->getSpikeLoc().at(enemyAt)->getX(), game->getSpikeLoc().at(enemyAt)->getY()-30, 1, 2, 15, true, getRenderer(), getAnimationList(), game);
                        b->setAttackDamage(2+level*2);
                        b->setHW(180+level*6, 180+level*6);
                        b->r = (60+level*3.5);
                        b->skillType = 2;
                        b->canDodge = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "purple"){
        if(level >= 1 && level<=20){
            Mix_PlayChannel(-1, purpleSound, 0);
            Bullet* b = new Bullet("Purple", Sx, Sy, 1, 2, 15, true, getRenderer(), getAnimationList(), game);
            b->setAttackDamage(3+level*3);
            b->setHW(220+level*6, 220+level*6);
            b->r = (80+level*3);
            b->skillType = 2;
            b->canDodge = true;
            game->getBulletLoc().push_back(b);
        }
    }
    else if(name == "lightning"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level/2; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Mix_PlayChannel(-1, lightning1, 0);
                        Bullet* b = new Bullet("Lightning", game->getSpikeLoc().at(enemyAt)->getX(), game->getSpikeLoc().at(enemyAt)->getY()-30, 1, 2, 15, true, getRenderer(), getAnimationList(), game);
                        b->setAttackDamage(8+level*6);
                        b->setHW(300, 150);
                        b->r = (100);
                        b->skillType = 2;
                        b->canDodge = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "lightningO"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level/2; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Mix_PlayChannel(-1, lightning2, 0);
                        Bullet* b = new Bullet("LightningO", game->getSpikeLoc().at(enemyAt)->getX(), game->getSpikeLoc().at(enemyAt)->getY(), 1, 2, 10, true, getRenderer(), getAnimationList(), game);
                        b->setAttackDamage(3+level*3);
                        b->setHW(120+level*8, 120+level*8);
                        b->r = (50+level*4);
                        b->skillType = 2;
                        b->canDodge = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "lightningC"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level/2; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Mix_PlayChannel(-1, lightning3, 0);
                        Bullet* b = new Bullet("LightningC", game->getSpikeLoc().at(enemyAt)->getX(), game->getSpikeLoc().at(enemyAt)->getY(), 1, 2, 20, true, getRenderer(), getAnimationList(), game);
                        b->setAttackDamage(6+level*5);
                        b->setHW(100+level*8, 100+level*8);
                        b->r = (45+level*4);
                        b->skillType = 2;
                        b->canDodge = true;
                        game->getBulletLoc().push_back(b);
                        enemyAt++;
                    }
                }
            }
        }
    }
    else if(name == "blast"){
        if(level >= 1 && level<=20){
            Mix_PlayChannel(-1, blastSound, 0);
            Bullet* b = new Bullet("Blast", getX(), getY(), 1, 2, 30, true, getRenderer(), getAnimationList(), game);
            b->setAttackDamage(5+level*4);
            b->setHW(400+level*20, 400+level*20);
            b->r = (200+level*10);
            b->skillType = 2;
            b->canDodge = false;
            game->getBulletLoc().push_back(b);
            enemyAt++;
        }
    }
}
void Player::upSkill(string name){
    bool b = true;
    int i;
    for(i = 0;i<skillList.size();++i){
        if(skillList.at(i)->name == name) {
            b = false;
            break;
        }
    }
    if(b){
        int cooldown = -1;
             if(name == "blue") cooldown = 4000;
        else if(name == "tornado") cooldown = 7000;
        else if(name == "fireburst") cooldown = 2000;
        else if(name == "blast") cooldown = 7500;
        else if(name == "lightning") cooldown = 5000;
        else if(name == "lightningO") cooldown = 6000;
        else if(name == "lightningC") cooldown = 7000;
        if (cooldown>0) skillList.push_back(new Skill(name, 1, cooldown));
    }
    else{
        skillList.at(i)->level++;
        skillList.at(i)->cooldown*=0.98;
    }
}
void Player::update(){
    timeBorn+=16.67;
    if(isDead()){
        setRun(false);
        setAttack(false);
        deadFrame++;
        if(deadFrame == 1){
            game->onPlayerDead();
        }
        else if(deadFrame < 6*20) setImage(getAnimationList()->getAnimation("WizDead", deadFrame/20 % 7));
        return;
    }
    for(int i = 0;i<skillList.size();++i){
        skillList.at(i)->timer+=16.67;
        if(skillList.at(i)->timer >= skillList.at(i)->cooldown){
            skillList.at(i)->timer = 0;
            castSkill(skillList.at(i)->name, skillList.at(i)->level, 0, 0);
        }
    }

    if (!canAttack()){
        attackFrame++;
        if(attackFrame > 7*5){
            setRun(true);
            setAttack(true);
            castSkill("purple", 1, clickedX, clickedY);
            attackFrame = 0;
        }
        else {
            setImage(getAnimationList()->getAnimation("WizAttack", attackFrame/5 % maxAttackFrame));
            return;
        }
    }

    if(vecX != 0 || vecY !=0){
        walkFrame++;
        if(walkFrame>maxRunFrame*7) walkFrame=0;
        setImage(getAnimationList()->getAnimation("WizRun", walkFrame/7 % maxRunFrame));
        if(walkFrame==1 || walkFrame==30) {
            Mix_PlayChannel(-1, footstep, 0);

        }
        if(walkFrame % 10 == 1){
            game->drawParticle(rand()%4+4, getX()+rand()%8, getY()+26+rand()%8);
            game->drawParticle(rand()%4+4, getX()+rand()%8, getY()+26+rand()%8);
            game->drawParticle(rand()%4+4, getX()+rand()%8, getY()+26+rand()%8);
            game->drawParticle(rand()%4+4, getX()+rand()%8, getY()+26+rand()%8);
        }
        addX(vecX*speed);
        addY(vecY*speed);
        if(SDL_GetTicks() % 4 == 1){
            game->createExp();
        }

    }

    else{
        setImage(getAnimationList()->getAnimation("WizIdle", (SDL_GetTicks()/120) % maxIdleFrame));
        walkFrame = 0;
    }


}
void Player::renderNPC(double x, double y){
    if(canRun()){
        if(vecX < 0){
            direct = 0;
        }
        else if(vecX > 0){
            direct = 1;
        }
    }
    if(direct == 0) this->renderCenterEx_Cam( x,  y, 'h');
        else        this->renderCenter_Cam( x,  y);
}
void Player::addXP(double xp){
    nowXP += xp;
    //cout<<"+ "<<xp<<"xp "<<nowXP<<"/"<<maxXP<<"\n";
    if(nowXP >= maxXP){
        this->levelUP();
    }
}
void Player::levelUP(){
    maxHP+=10;
    HP+=10;
    HP+=(maxHP-HP)/2;
    nowXP -= maxXP;
    level++;
    maxXP += level*15;
    game->onPlayerLevelUp();
}
//spikeeeeeeeeeeeeee
Spike::Spike(string name, double hp, double maxHP, double attackDamage, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game){
    this->game = game;
    this->id = animation->convertNameToID(name);
    maxRunFrame = animation->getMaxFrameAnimation(name) - 1;
    timeBorn = SDL_GetTicks();

    setImage(animation->getAnimation(name, 0));
    SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);

    setHW(getPos().h, getPos().w);
    setXY(x, y);
    setScale(scale);
    setName(name);
    setHP(hp);
    setMaxHP(maxHP);
    setAttackDamage(attackDamage);
    setSpeed(speed);
    setAnimationList(animation);
    setRenderer(renderer);
    updateR();
}
void Spike::update(double _x, double _y){
    if(isHitted){
        isHitted = false;
        setImage(getAnimationList()->getAnimationWithID(id, maxRunFrame));
    }
    else setImage(getAnimationList()->getAnimationWithID(id, ((SDL_GetTicks()+int(timeBorn))/80) % maxRunFrame));
    updateVec(_x,_y);

    addX(speed*vecX);
    addY(speed*vecY);
    if(collideWith(game->p)){
        game->p->damaged(this);
        if(game->p->hitCount < 20){
            game->p->hitCount+=2;
        }
        game->p->isHitted = true;
    }

}

//bulletttttttttttt

Bullet::Bullet(string name, double x, double y, double scale, double speed, int speedOfFrame, bool loopAnimation, SDL_Renderer* renderer, AnimationList* animation, Game* game){
    this->game = game;
    this->id = animation->convertNameToID(name);
    this->speedOfFrame = speedOfFrame;
    this->numberOfFrame = animation->getMaxFrameAnimation(name);
    this->loopAnimation = loopAnimation;
    this->frame = 0;
    time = 0;
    timeBorn = SDL_GetTicks();

    setImage(animation->getAnimationWithID(id, 0));
    SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);

    setHW(getPos().h, getPos().w);
    setXY(x, y);
    setScale(scale);
    setSpeed(speed);
    setRenderer(renderer);
    setAnimationList(animation);
    updateR();

    isEnemy = false;
}

void Bullet::update(double timeAdd){
    time += timeAdd;
    timeT += timeAdd;
    particleCount++;
    //Skill ban
    if(skillType == 0){
        //tren duong bay
        if(skillStatus == 0){
            speed*=1.01;
            if(speed>1.4){
                speed = speed*1.04+0.0002;
            }
            if(speed>50){
                skillStatus = -1;
                return;
            }
            if(vecX + vecY == 0){
                updateVec2(game->p->getX() + rand()% 1000 - 500, game->p->getY() + rand()% 1000 - 500);
            }
            if(victim != NULL && !victim->isDead()) {
                updateVec2(victim->getX(), victim->getY());
            }

            if(distanceBetween(game->p) > 1000){
                skillStatus = -1;
                return;
            }
            setImage(getAnimationList()->getAnimationWithID(id, 0));
            addX(speed*vecX);
            addY(speed*vecY);
            if(particleCount > 2){
                particleCount = 0;
                game->drawParticle(3, getX(), getY());
            }
            int t = game->getSpikeLoc().size();
            for(int i=0;i<t;++i){
                if(!game->getSpikeLoc().at(i)->isDead()){
                    if(collideWith(game->getSpikeLoc().at(i))){
                        game->getSpikeLoc().at(i)->damaged(this);
                        skillStatus = 1;
                        time = 0;
                        //Mix_PlayChannel(-1, hitSound, 0);
                        if(damageType == 0) break;
                    }
                }
            }
        }
        //trung muc tieu
        else if(skillStatus == 1){
            while(time >= speedOfFrame){
                frame++;
                time -= speedOfFrame;
            }
            if(frame < numberOfFrame) setImage(getAnimationList()->getAnimationWithID(id, frame));
            else skillStatus = -1;
        }
    }
    else if(skillType == 1){
        if(skillStatus == 0){
            if(timeT > maxTime){
                skillStatus = -1;
            }
            if(victim != NULL && !victim->isDead() && vecX+vecY==0) {
                updateVec2(victim->getX(), victim->getY());
            }
            else if(vecX + vecY == 0){
                updateVec2(game->p->getX() + rand()% 1000 - 500, game->p->getY() + rand()% 1000 - 500);
            }

            if(distanceBetween(game->p) > 1000){
                skillStatus = -1;
                return;
            }
            while(time >= speedOfFrame){
                frame++;
                time -= speedOfFrame;
            }
            if(frame < numberOfFrame) setImage(getAnimationList()->getAnimationWithID(id, frame));
                else frame = 0;
            addX(speed*vecX);
            addY(speed*vecY);
            int t = game->getSpikeLoc().size();
            for(int i=0;i<t;++i){
                if(!game->getSpikeLoc().at(i)->isDead()){
                    if(collideWith(game->getSpikeLoc().at(i))){
                        game->getSpikeLoc().at(i)->damaged(this);
                    }
                }
            }
        }
    }
    else if(skillType == 2){
        if(skillStatus == 0){
            while(time >= speedOfFrame){
                frame++;
                time -= speedOfFrame;
            }
            if(frame/3 < numberOfFrame) setImage(getAnimationList()->getAnimationWithID(id, frame/3));
                else skillStatus = -1;
            int t = game->getSpikeLoc().size();
            for(int i=0;i<t;++i){
                if(!game->getSpikeLoc().at(i)->isDead()){
                    if(collideWith(game->getSpikeLoc().at(i))){
                        game->getSpikeLoc().at(i)->damaged(this);
                    }
                }
            }
        }
    }
    //Sk
}

//
Exp::Exp(double xp, double x, double y, SDL_Renderer* renderer, AnimationList* animation){
    this->xp = xp;
    if (xp>100) setImage(animation->getAnimation("Exp", 3));
    else if (xp>50) setImage(animation->getAnimation("Exp", 2));
    else if (xp>20) setImage(animation->getAnimation("Exp", 1));
    else if (xp>0) setImage(animation->getAnimation("Exp", 0));
    setRenderer(renderer);
    SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);
    setHW(getPos().h, getPos().w);
    setXY(x, y);
}
