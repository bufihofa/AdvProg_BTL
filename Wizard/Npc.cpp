#include "Npc.h"
#include "Game.h"
#include "QTree.h"

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


}

void Player::playAttackAnimation(){
    if(canAttack()){
        setRun(false);
        setAttack(false);
        setAttackFrame(-1);
    }
}
void Player::castSkill(string name, int level){
    int enemyAt = 0;
    if(name == "fireburst"){
        if(level >= 1 && level<=20){
            int t = game->getSpikeLoc().size();
            if(t>0){
                for(int i = 0;i <1+level; ++i){
                    while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                        enemyAt++;
                    }
                    if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                        Bullet* b = new Bullet("Burst1", getX(), getY(), 0.5, 1, 12, true, getRenderer(), getAnimationList(), game);
                        b->victim = game->getSpikeLoc().at(enemyAt);
                        b->setAttackDamage(50+level*10);
                        b->setR(1);
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
                        Bullet* b = new Bullet("Tornado", getX(), getY(), 1, 2, 15, true, getRenderer(), getAnimationList(), game);
                        b->victim = game->getSpikeLoc().at(i%t);
                        b->setAttackDamage(1+level/3);
                        b->setHW(180, 180);
                        b->setR(60);
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
                        b->setAttackDamage(2+level);
                        b->setHW(180+level*6, 180+level*6);
                        b->setR(60+level*4);
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
            int t = game->getSpikeLoc().size();
            if(t>0){
                while(enemyAt<t && game->getSpikeLoc().at(enemyAt)->isDead()){
                    enemyAt++;
                }
                if(enemyAt < t && !game->getSpikeLoc().at(enemyAt)->isDead()){
                    Bullet* b = new Bullet("Purple", game->getSpikeLoc().at(enemyAt)->getX(), game->getSpikeLoc().at(enemyAt)->getY(), 1, 2, 15, true, getRenderer(), getAnimationList(), game);
                    b->setAttackDamage(3+level*1.5);
                    b->setHW(220+level*6, 220+level*6);
                    b->setR(80+level*3);
                    b->skillType = 2;
                    b->canDodge = false;
                    game->getBulletLoc().push_back(b);
                    enemyAt++;
                }

            }
        }
    }
}
void Player::update(){
    timeBorn+=16.67;
    timeTemp+=16.67;
    if(timeTemp>2000){
        castSkill("fireburst", 10);
        timeTemp-=2000;
    }

    if (!canAttack()){
        nextAttackFrame();
        if(getAttackFrame() > 7*5){
            setRun(true);
            setAttack(true);
            castSkill("purple", 3);
            //game->getBulletLoc().push_back(new Bullet("Burst1", getX()-400, getY()-400, getX()+2000, getY()+2000, 0.5, 4, 40, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()+200, getY()-200, getX()+200, getY()-200, 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()-200, getY()-200, getX()-200, getY()-200, 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()-200, getY()+200, getX()-200, getY()+200, 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX(), getY()+200, getX(), getY()+200, 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()-200, getY(), getX()-200, getY(), 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()+200, getY(), getX()+200, getY(), 2, 5, 20, true, getRenderer(), getAnimationList(), game));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX(), getY()-200, getX(), getY()-200, 2, 5, 20, true, getRenderer(), getAnimationList(), game));
        }
        else {
            setImage(getAnimationList()->getAnimation("WizAttack", getAttackFrame()/5 % maxAttackFrame));
            return;
        }
    }

    if(vecX != 0 || vecY !=0){
        setImage(getAnimationList()->getAnimation("WizRun", (SDL_GetTicks()/180) % maxRunFrame));
        addX(vecX*speed);
        addY(vecY*speed);
        if(SDL_GetTicks() % 4 == 1){
            game->createExp();
        }

    }

    else setImage(getAnimationList()->getAnimation("WizIdle", (SDL_GetTicks()/120) % maxIdleFrame));

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
    while(nowXP >= maxXP){
        this->levelUP();
    }
}
void Player::levelUP(){
    nowXP -= maxXP;
    level++;
    maxXP += level*10;
    //cout<<"- LEVEL UP "<<level-1<<"->"<<level<<" -- "<<nowXP<<"/"<<maxXP<<"\n";
}
//spikeeeeeeeeeeeeee
Spike::Spike(string name, double hp, double maxHP, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game){
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

    //if(game->g->isSafeZone(getX()+speed*vecX, getY()+speed*vecY)){
    addX(speed*vecX);
    addY(speed*vecY);
    //}

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

//renew frame
/*
void Bullet::update(double timeAdd){
    if(victim != NULL) setToXY(victim->getX(), victim->getY());
    time += timeAdd;
    if(time >= speedOfFrame){
        frame++;
        time -= speedOfFrame;
    }
    if(frame < numberOfFrame) setImage(getAnimationList()->getAnimationWithID(id, frame));
        else if(loopAnimation) frame = 0;

    double temp = getDirectXY();
    double dX = temp*(toX-getX());
    double dY = temp*(toY-getY());

    //if(dX < 0) direct = 0;
    //else if(dX > 0) direct = 1;

    addX(dX);
    addY(dY);

}
*/
void Bullet::update(double timeAdd){
    time += timeAdd;
    timeT += timeAdd;
    particleCount++;
    //Skill ban
    if(skillType == 0){
        //tren duong bay
        if(skillStatus == 0){
            speed*=1.01;
            if(speed>1.5){
                speed = speed*1.04+0.0001;
            }
            if(speed>40){
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
