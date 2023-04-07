#ifndef NPC_H
#define NPC_H

#include <bits/stdc++.h>
#include "Animation.h"
#include "Game.h"
#include "Entity.h"
//######################### ENTITY ##############################################
class NPC: public Entity{
protected:
    double toX;
    double toY;

    int maxAttackFrame;
    int maxRunFrame;
    int maxIdleFrame;

    string name;
    int id;
    double HP;
    double maxHP;
    double speed;

    bool Run = true;
    bool Attack = true;

    int direct = 0;
    int attackFrame = 0;
    int timeBorn = 0;

    Game* game;
    AnimationList* animationList;
public:

    void setAnimationList(AnimationList* animation)   {this->animationList = animation;}
    AnimationList* getAnimationList()                 {return animationList;}

    void setAttackFrame(int i)  {attackFrame = i;}
    int  getAttackFrame()       {return attackFrame;}
    void nextAttackFrame()      {attackFrame++;}

    double getHP()     {return this->HP;}
    double getMaxHP()  {return this->maxHP;}
    double getSpeed()  {return this->speed;}

    void setHP(double HP)        {this->HP = HP;}
    void setMaxHP(double maxHP)  {this->maxHP = maxHP;}
    void setSpeed(double speed)  {this->speed = speed;}

    void setRun(bool a)     {Run = a;}
    void setAttack(bool a)  {Attack = a;}

    bool canRun()     {return Run;}
    bool canAttack()  {return Attack;}

    void setToXY(double toX, double toY){
        this->toX = toX;
        this->toY = toY;
    }
    void setToX(double toX){this->toX = toX;}
    void setToY(double toY){this->toY = toY;}

    double getToX() {return toX;}
    double getToY() {return toY;}

    double getDirectXY(){
        return min(1.0, getSpeed()/sqrt((toX-getX())*(toX-getX()) + (toY-getY())*(toY-getY())));
    }

    void setName(string name){this->name = name;}
    string getName()         {return this->name;}

    void renderNPC(double x, double y){
        if(direct == 0) this->renderCenterEx_Cam( x,  y, 'h');
            else        this->renderCenter_Cam( x,  y);
    }

};


//######################## PLAYER ###############################################
class Player: public NPC{
private:
    double direction_x;
    double direction_y;
public:
    Player();
    Player(double hp, double maxHP, double speed, double scale, AnimationList* animation, SDL_Renderer* renderer, Game* game);
    void playAttackAnimation();
    void updateDirect(double x, double y);
    void update();
    void renderNPC(double x, double y);

};


//######################## SPIKE ################################################
class Spike: public NPC{
public:
    Spike(){}
    Spike(string name, double hp, double maxHP, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game);
    void update();
    //
    void renderNPC(double x, double y){this->renderCenter_Cam( x,  y);}

};


//######################## ENEMY ###############################################
class Enemy: public NPC{
public:
    Enemy(){}
    Enemy(string name, double hp, double maxHP, double speed, double scale, double x, double y, AnimationList* animation, SDL_Renderer* renderer, Game* game);
    void update();
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
    Bullet(){}
    Bullet(string name, double x, double y, double toX, double toY, double scale, double speed, int speedOfFrame, bool loopAnimation, SDL_Renderer* renderer, AnimationList* animation, Game* game);
    void update(double timeAdd);
    //

    int getSpeedOfFrame()   {return this->speedOfFrame;}
    int getNumberOfFrame()  {return this->numberOfFrame;}
    int getFrame()   {return this->frame;}
    int getTime()    {return this->time;}
    int getID()      {return this->id;}
};
#endif // NPC_H
