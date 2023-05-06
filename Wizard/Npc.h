#pragma once
#include <bits/stdc++.h>
#include "Animation.h"
#include "Entity.h"
using namespace std;
class Game;
class Skill{
public:
    string name;
    int level;
    double cooldown;
    double timer;

    Skill(string name, int level, double cooldown){
        this->name = name;
        this->level = level;
        this->cooldown = cooldown;
        this->timer = cooldown*0.8;
    }
};
//######################### NPC #################################################
class NPC: public Entity{
protected:

    int maxAttackFrame;
    int maxRunFrame;
    int maxIdleFrame;

    string name;
    int id;
    double HP;
    double maxHP;
    double speed;
    double attackDamage = 100;

    bool Run = true;
    bool Attack = true;

    int direct = 0;
    double timeBorn = 0;

    Game* game;
    AnimationList* animationList;



public:
    double toX;
    double toY;
    double vecX = 0;
    double vecY = 0;
    bool isHitted = false;
    int hitCount = 0;
    int hitSoundCount = 0;
    bool isEnemy = true;
    int attackFrame = 0;
    int deadFrame = 0;
    int walkFrame = 0;
    double r = 10;

    void setAnimationList(AnimationList* animation)   {this->animationList = animation;}
    AnimationList* getAnimationList()                 {return animationList;}

    double getHP()     {return this->HP;}
    double getMaxHP()  {return this->maxHP;}
    double getSpeed()  {return this->speed;}
    double getAttackDamage() {return this->attackDamage;}
    bool isDead()   {return HP<=0;}

    void setHP(double HP)        {this->HP = HP;}
    void setMaxHP(double maxHP)  {this->maxHP = maxHP;}
    void setSpeed(double speed)  {this->speed = speed;}
    void setAttackDamage(double attackDamage)   {this->attackDamage = attackDamage;}
    void setRun(bool a)     {Run = a;}
    void setAttack(bool a)  {Attack = a;}

    bool canRun()     {return Run;}
    bool canAttack()  {return Attack;}

    void damaged(NPC* attacker){
        this->HP -= attacker->getAttackDamage();
        isHitted = true;
    }

    void setToXY(double toX, double toY){
        this->toX = toX;
        this->toY = toY;
    }

    double getToX() {return toX;}
    double getToY() {return toY;}


    void setName(string name){this->name = name;}
    string getName()         {return this->name;}

    void renderNPC(double x, double y){
        if(direct == 0) this->renderCenterEx_Cam( x,  y, 'h');
            else        this->renderCenter_Cam( x,  y);
    }

    bool collideWith(NPC* b){
        return sqrt((b->getX()-getX()) * (b->getX()-getX()) + (b->getY()-getY())*(b->getY()-getY())) < r + b->r ;
    }
    bool collideWith2(NPC* b){
        return ((b->getX()-getX()) * (b->getX()-getX()) + (b->getY()-getY())*(b->getY()-getY())) < (r + b->r)*(r + b->r)*0.6 ;
    }
    void updateR(){
        r = max(getW(), getH())/2;
    }
    void updateVec(double dx, double dy){
        dx -= getX();
        dy -= getY();
        if(abs(dx)<1 && abs(dy)<1){
            vecX = 0;
            vecY = 0;
            return;
        }
        double delta = sqrt(dx*dx+dy*dy);
        vecX = dx/delta;
        vecY = dy/delta;
    }

    void updateVec2(double dx, double dy){
        dx -= getX();
        dy -= getY();
        double delta = sqrt(dx*dx+dy*dy);
        if(delta == 0){
            vecX = (rand()%50+50)/100;
            vecY = 1 - vecX*vecX;
        }
        vecX = dx/delta;
        vecY = dy/delta;
    }

    double distanceBetween(NPC* npc){
        return sqrt((getX()-npc->getX())*(getX()-npc->getX())+(getY()-npc->getY())*(getY()-npc->getY()));
    }
    double distanceBetween2(NPC* npc){
        return (getX()-npc->getX())*(getX()-npc->getX())+(getY()-npc->getY())*(getY()-npc->getY());
    }
};


//######################## PLAYER ###############################################
class Player: public NPC{
private:
    double nowXP = 0;
    double maxXP = 200;
    double level = 1;
    double timeTemp = 0;
    double clickedX;
    double clickedY;
public:
    vector<Skill*> skillList;
    Player();
    Player(double hp, double maxHP, double speed, double scale, AnimationList* animation, SDL_Renderer* renderer, Game* game);
    void playAttackAnimation(double x, double y);
    void updateDirect(double x, double y);
    void update();
    void renderNPC(double x, double y);
    void addXP(double xp);
    void levelUP();
    void upSkill(string name);
    void castSkill(string name, int level, double Sx, double Sy);
    //
    void setXP(double xp){ nowXP = xp;}
    double getXP(){ return this->nowXP;}
    double getXPPro(){ return nowXP/maxXP;}
    double getHPPro(){ return HP/maxHP;}
};


//######################## SPIKE ################################################
class Spike: public NPC{
public:
    int deadAnimation = -1;
    int mousePoint = 0;
    Spike(){}
    Spike(string name, double hp, double maxHP, double attackDamage, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game);
    void update(double _x, double _y);
    //
    void renderNPC(double x, double y){this->renderCenter_Cam( x,  y);}

};



//######################## BULLET ##############################################
class Bullet: public NPC{
protected:
    double time;
    int speedOfFrame;
    int numberOfFrame;
    int frame;
    bool loopAnimation;


public:

    int skillType = 0;
    int skillStatus = 0;
    int damageType = 0;
    int maxTime = 0;
    double timeT = 0;
    int particleCount = 0;
    bool hasParticle = false;
    bool canDodge = false;
    NPC* victim = NULL;

    Bullet(){}
    Bullet(string name, double x, double y, double scale, double speed, int speedOfFrame, bool loopAnimation, SDL_Renderer* renderer, AnimationList* animation, Game* game);
    void update(double timeAdd);
    //

    int getSpeedOfFrame()   {return this->speedOfFrame;}
    int getNumberOfFrame()  {return this->numberOfFrame;}
    int getFrame()   {return this->frame;}
    int getTime()    {return this->time;}
    int getID()      {return this->id;}
};
//######################## EXP ##############################################
class Exp: public Entity{
protected:
    double xp = 1;
    double speed = 0.02;
    bool collect = false;
public:
    Exp(double xp, double x, double y, SDL_Renderer* renderer, AnimationList* animation);
    double getDistance(double x1, double y1, double x2, double y2){
        return(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
    }
    double getXP(){
        return xp;
    }
    bool check(double x, double y, double r){
        if(!collect){
            collect = getDistance(getX(), getY(), x, y) < r;
            if(getDistance(getX(), getY(), x, y) > 5000){
                xp = 0;
                return true;
            }
        }
        else{
            addX((x-getX())*speed);
            addY((y-getY())*speed);
            speed += 0.005;
            return (getDistance(getX(), getY(), x, y) < 20);
        }
        return false;
    }
};

