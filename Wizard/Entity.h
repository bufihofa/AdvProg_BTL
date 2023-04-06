#ifndef ENTITY__H
#define ENTITY__H

#include <iostream>
#include "SDL_utils.h"

class Point{
private:
    double x,y,h,w;
public:
    Point(){
        x = 0;
        y = 0;
        h = 500;
        w = 500;
    }
    double getX()  {return this->x;}
    void setX(double x)    {this->x=x;}

    double getY()  {return this->y;}
    void setY(double y)    {this->y=y;}

    double getH()  {return this->h;}
    void setH(double h)    {this->h=h;}

    double getW()  {return this->w;}
    void setW(double w)    {this->w=w;}
};
class Entity{

private:
    Point pos_double;
    SDL_Rect pos;
    SDL_Rect pos_center;

    SDL_Renderer* renderer;
	SDL_Texture* image;

	double angle = 0;

public:
    double getX()  {return pos_double.getX();}
    void setX(double x)    {pos_double.setX(x);  pos.x=pos_double.getX();}

    double getY()  {return pos_double.getY();}
    void setY(double y)    {pos_double.setY(y);  pos.y=pos_double.getY();}

    double getH()  {return pos_double.getH();}
    void setH(double h)    {pos_double.setH(h);  pos.h=pos_double.getH();}

    double getW()  {return pos_double.getW();}
    void setW(double w)    {pos_double.setW(w);  pos.w=pos_double.getW();}
    void setCenterX(double _w)  {this->setX(_w/2 - this->getW()/2);}
    double getCenterX(){
        return getX()+getW()/2;
    }
    double getCenterY(){
        return getY()+getH()/2;
    }

    void setXY(double x,double y){
        this->setX(x);
        this->setY(y);
    }
    void setHW(double h,double w){
        this->setW(w);
        this->setH(h);
    }
    void setAC(double x, double y){
        this->setX(x-getW()/2.0);
        this->setY(y-getH()/2.0);
    }

    double getAngle(){
        return this->angle;
    }
    void setAngle(double angle){
        this->angle = angle;
    }
    void setScale(double x){
        this->setH(this->getH()*x);
        this->setW(this->getW()*x);

    }
    void addX(double x){this->setX(this->getX()+x);}
    void addY(double y){this->setY(this->getY()+y);}
    void addH(double h){this->setH(this->getH()+h);}
    void addW(double w){this->setW(this->getW()+w);}

    bool isClicked(int x, int y){
        return ((x >= getX()) && (x <= getX()+getW()) && (y >= getY()) && (y <= getY() + getH()));
    }
    bool isClickedCenter(int x, int y){
        return ((x >= getX()-getW()/2) && (x <= getX()+getW()/2) && (y >= getY()-getH()/2) && (y <= getY()+getH()/2));
    }
    Entity(){}
    Entity(double x, double y, string path, SDL_Renderer* renderer){
        setXY(x, y);
        setRenderer(renderer);
        loadIMG(path);
        SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);
        setHW(getPos().h, getPos().w);
    }
    Entity(double x, double y, SDL_Texture* img, SDL_Renderer* renderer){
        setXY(x, y);
        setRenderer(renderer);
        setImage(img);
        SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);
        setHW(getPos().h, getPos().w);
    }

    void render()   {SDL_RenderCopyEx(renderer, image, NULL, &pos, angle, NULL, SDL_FLIP_NONE);}
    void renderCenter(){
        pos_center.h = getH();
        pos_center.w = getW();
        pos_center.x = getX() - getH()/2.0;
        pos_center.y = getY() - getW()/2.0;
        SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_NONE);
    }
    void renderCenterEx(char _c){
        pos_center.h = getH();
        pos_center.w = getW();
        pos_center.x = getX() - getH()/2.0;
        pos_center.y = getY() - getW()/2.0;
        if(_c == 'h')  SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_HORIZONTAL);
            else      SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_VERTICAL);
    }
    void renderCenter_Cam(double dx, double dy){
        pos_center.h = getH();
        pos_center.w = getW();
        pos_center.x = getX() - getH()/2.0 - dx;
        pos_center.y = getY() - getW()/2.0 - dy;
        SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_NONE);
    }
    void renderCenterEx_Cam(double dx, double dy, char _c){
        pos_center.h = getH();
        pos_center.w = getW();
        pos_center.x = getX() - getH()/2.0 - dx;
        pos_center.y = getY() - getW()/2.0 - dy;
        if(_c == 'h')  SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_HORIZONTAL);
        else    SDL_RenderCopyEx(renderer, image, NULL, &pos_center, angle, NULL, SDL_FLIP_VERTICAL);
    }




    void setRenderer(SDL_Renderer* renderer)    {this->renderer = renderer;}
    void setImage(SDL_Texture* image)   {this->image = image;}
    void loadIMG(string path){image = loadTexture(path, renderer);}
    SDL_Renderer* getRenderer() {return renderer;}
    SDL_Texture* getImage() {return image;}
    SDL_Rect& getPos()  {return pos;}

    void clearEntity(){
        SDL_DestroyTexture(image);
        renderer = NULL;
        image = NULL;
    }
};



#endif //ENTITY__H

