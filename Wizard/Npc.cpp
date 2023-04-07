#include "Npc.h"
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
}

void Player::playAttackAnimation(){
    if(canAttack()){
        setRun(false);
        setAttack(false);
        setAttackFrame(-1);
    }
}
void Player::updateDirect(double x, double y){
    double dX = x-600;
    double dY = y-400;

    if(abs(dX) < 30 && abs(dY) < 30){
        direction_y = 0;
        direction_x = 0;
    }
    else if(dX == 0){
        direction_y = dY/abs(dY)*getSpeed();
        direction_x = 0;
    }
    else if(dY == 0){
        direction_y = 0;
        direction_x = dX/abs(dX)*getSpeed();
    }
    else{
        double a = abs(dX/dY);
        double abs_dY = abs(sqrt((getSpeed()*getSpeed())/(1.0+a*a)));
        double abs_dX = a*abs_dY;

        direction_x = abs_dX * dX/abs(dX);
        direction_y = abs_dY * dY/abs(dY);
    }
}
void Player::update(){
    if (!canAttack()){
        nextAttackFrame();
        if(getAttackFrame() > 7*5){
            setRun(true);
            setAttack(true);
            //game->playerCastSpell("Electric", getX()+200, getY()+200, getX()+200, getY()+200, 2, 2, 100, false, getRenderer(), getAnima());
            //Game::bullet.push_back(new Bullet(name, x, y, toX, toY, scale, speed, speedOfFrame, loopAnimation, renderer, animation));
            //game->getBulletLoc().push_back(new Bullet("Electric", getX()+200, getY()+200, getX()+2000, getY()+2000, 2, 5, 100, true, getRenderer(), getAnima()));
            game->getBulletLoc().push_back(new Bullet("Electric", getX()+200, getY()+200, getX()+200, getY()+200, 2, 5, 20, false, getRenderer(), getAnimationList(), game));
            game->getBulletLoc().push_back(new Bullet("Electric", getX()+200, getY()-200, getX()+200, getY()-200, 2, 5, 20, false, getRenderer(), getAnimationList(), game));
            game->getBulletLoc().push_back(new Bullet("Electric", getX()-200, getY()-200, getX()-200, getY()-200, 2, 5, 20, false, getRenderer(), getAnimationList(), game));
            game->getBulletLoc().push_back(new Bullet("Electric", getX()-200, getY()+200, getX()-200, getY()+200, 2, 5, 20, false, getRenderer(), getAnimationList(), game));
            //cout<<game->getBulletLoc().size()<<" size\n";
        }
        else {
            setImage(getAnimationList()->getAnimation("WizAttack", getAttackFrame()/5 % maxAttackFrame));
            return;
        }
    }

    if(direction_x != 0 || direction_y !=0){
        setImage(getAnimationList()->getAnimation("WizRun", (SDL_GetTicks()/120) % maxRunFrame));
        addX(direction_x);
        addY(direction_y);
    }

    else setImage(getAnimationList()->getAnimation("WizIdle", (SDL_GetTicks()/120) % maxIdleFrame));
}
void Player::renderNPC(double x, double y){
    if(direction_x < 0){
        direct = 0;
    }
    else if(direction_x > 0){
        direct = 1;
    }
    if(direct == 0) this->renderCenterEx_Cam( x,  y, 'h');
        else        this->renderCenter_Cam( x,  y);
}
//enemyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
Enemy::Enemy(string name, double hp, double maxHP, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game){
    this->game = game;
    maxAttackFrame = animation->getMaxFrameAnimation(name+"Attack");
    maxRunFrame = animation->getMaxFrameAnimation(name+"Run");

    setImage(animation->getAnimation(name+"Run", 0));
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
}
void Enemy::update(){
    if (!canAttack()){
        nextAttackFrame();
        if(getAttackFrame() >= maxAttackFrame*5){
            setRun(true);
            setAttack(true);
        }
        else {
            setImage(getAnimationList()->getAnimation(name+"Attack", getAttackFrame()/5 % maxAttackFrame));
            return;
        }
    }
    double temp = getDirectXY();
    double dX = temp*(toX-getX());
    double dY = temp*(toY-getY());

    if(dX < 0) direct = 0;
    else if(dX > 0) direct = 1;

    if(temp<1){
        setImage(getAnimationList()->getAnimation(name+"Run", (SDL_GetTicks()/120) % maxRunFrame));
        addX(dX);
        addY(dY);
    }

}


//spikeeeeeeeeeeeeee
Spike::Spike(string name, double hp, double maxHP, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game){
    this->game = game;
    maxRunFrame = animation->getMaxFrameAnimation(name);
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
}
void Spike::update(){
    double temp = getDirectXY();
    double dX = temp*(toX-getX());
    double dY = temp*(toY-getY());
    setImage(getAnimationList()->getAnimation(name, ((SDL_GetTicks()+timeBorn)/80) % maxRunFrame));
    if(temp<1){
        addX(dX);
        addY(dY);
    }
}
//bulletttttttttttt

Bullet::Bullet(string name, double x, double y, double toX, double toY, double scale, double speed, int speedOfFrame, bool loopAnimation, SDL_Renderer* renderer, AnimationList* animation, Game* game){
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
    setToXY(toX, toY);
    setScale(scale);
    setSpeed(speed);
    setRenderer(renderer);
    setAnimationList(animation);
}
//renew frame
void Bullet::update(double timeAdd){
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

    if(dX < 0) direct = 0;
    else if(dX > 0) direct = 1;

    addX(dX);
    addY(dY);
}

