#ifndef MENU__H
#define MENU__H

#include "Entity.h"
#include <bits/stdc++.h>

class mButton: public Entity{
private:
    bool isHighlight = false;
    bool canHL = false;
    Point po;
    string name;
public:
    mButton(){}
    mButton(string name, double x, double y, string path, SDL_Renderer* renderer, double scale, bool isCenter, bool canHL){

        this->name = name;
        setRenderer(renderer);
        loadIMG(path);
        SDL_QueryTexture(getImage(), NULL, NULL, &getPos().w, &getPos().h);

        setHW(getPos().h, getPos().w);

        this->setScale(scale);
        setXY(x, y);
        if(isCenter) this->setCenterX(1200);
        this->canHL = canHL;
    }
    bool isHL(){return isHighlight;}

    void HL(){
        if(canHL && !isHighlight){
            this->setScale(1.15);
            isHighlight = true;
        }
    }
    void unHL(){
        if(isHighlight){
            this->setScale(100.0/115.0);
            isHighlight = false;
        }
    }
    string getName()  {return this->name;}
};
class Menu{
private:
    Entity panel;
    deque<mButton> buttonList;
    SDL_Renderer* renderer;
public:
    Menu(){}
    Menu(SDL_Renderer* renderer){
        this->setRenderer(renderer);
    }
    Menu(SDL_Renderer* renderer, string path){
        this->setRenderer(renderer);
        panel = Entity(600, 400, path, renderer);
        panel.setAC(600, 400);
    }
    void setRenderer(SDL_Renderer* renderer){
        this->renderer = renderer;
    }
    void addButton(string name, double x, double y, string path, SDL_Renderer* renderer, double scale, bool isCenter, bool canHL){
        buttonList.push_back(mButton(name, x, y, path, renderer, scale, isCenter, canHL));
    }
    Entity* getPanel(){
        return &panel;
    }
    mButton* getButton(int stt_button){
        if(stt_button < buttonList.size())
            return &buttonList.at(stt_button);
    }
    void checkMouseMove(double x, double y){
        if(!buttonList.empty()){
            for(int i=0;i<buttonList.size();++i){
                buttonList.at(i).unHL();
            }
            for(int i=0;i<buttonList.size();++i){
                if(buttonList.at(i).isClickedCenter(x, y)){
                    buttonList.at(i).HL();
                    return;
                }
            }
        }
    }
    void forceHL(int i){
        if(i < buttonList.size())
            buttonList.at(i).HL();
    }
    void forceUnHL(){
        if(!buttonList.empty()){
            for(int i=0;i<buttonList.size();++i){
                buttonList.at(i).unHL();
            }
        }
    }
    string checkMouseClick(double x, double y){
        if(!buttonList.empty()){
            for(int i=0;i<buttonList.size();++i){
                if(buttonList.at(i).isClickedCenter(x, y)){
                    return buttonList.at(i).getName();
                }
            }
        }
        return "-1";
    }
    void render(){
        panel.render();
        if(!buttonList.empty()){
            for(int i=0;i<buttonList.size();++i){
                buttonList.at(i).renderCenter();
            }
        }
    }
};

void openMenu(SDL_Window* window, SDL_Renderer* renderer, int _width, int _height);
#endif //ENTITY__H

