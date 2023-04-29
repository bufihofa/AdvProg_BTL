#pragma once
#include <bits/stdc++.h>
#include "SDL_utils.h"
using namespace std;


class Animation{
private:
    vector<SDL_Texture*> frameList;
    int numberOfFrame;
    int speedOfFrame;
    int h, w;
    SDL_Renderer* renderer;
public:
    Animation(){}
    Animation(string path,int numberOfFrame, int speedOfFrame, SDL_Renderer* renderer){

        this->numberOfFrame = numberOfFrame;
        this->speedOfFrame = speedOfFrame;
        this->renderer = renderer;

        for(int i=0;i<numberOfFrame;++i){
            frameList.push_back(loadTexture(path + to_string(i) + ".png", renderer));
            SDL_QueryTexture(frameList.at(i), NULL, NULL, &w, &h);
        }
    }
    int getSpeedOfFrame(){
        return this->speedOfFrame;
    }
    int getNumberOfFrame(){
        return this->numberOfFrame;
    }
    double getH(){
        return this->h;
    }
    double getW(){
        return this->w;
    }
    void clearAnimation(){
        for(int i=0;i<numberOfFrame;++i){
            SDL_DestroyTexture(frameList[i]);
        }
        renderer = NULL;
    }
    SDL_Texture* getFrame(int i){
        if(i>frameList.size()-1) cout<<"[Animation.h] ERROR: Animation Get Frame > Animation Size\n";
        return frameList.at(i);
    }
};

class AnimationList{
private:
    vector<Animation> animationList;
    map<string, int> animationHash;
public:
    AnimationList(){}

    void loadAnimation(string name, string path, int numberOfFrame, int speedOfFrame, SDL_Renderer* renderer){
        if(animationHash[name] > 0){
            cout<<"[Animation.h] ERROR: Animation '"<<name<<"': load failed - name is duplicated\n";
            return;
        }
        animationList.push_back(Animation(path, numberOfFrame, speedOfFrame, renderer));
        animationHash[name] = animationList.size();
        cout<<"[Animation.h] Loaded Animation '"<<name<<"'\n";

    }
    SDL_Texture* getAnimation(string name, int frame){
        int t = animationHash[name]-1;
        if(t<0){
            cout<<"[Animation.h] ERROR: Animation '"<<name<<"' does not exist\n";
        }
        return animationList.at(t).getFrame(frame);
    }
    SDL_Texture* getAnimationWithID(int id, int frame){
        if(id>=animationList.size()){
            cout<<"[Animation.h] ERROR: Animation with ID '"<<id<<"' does not exist\n";
        }
        return animationList.at(id).getFrame(frame);
    }
    int convertNameToID(string name){
        int t = animationHash[name]-1;
        if(t<0){
            cout<<"[Animation.h] ERROR: Animation '"<<name<<"' does not exist\n";
            return 0;
        }
        return t;
    }
    int getMaxFrameAnimation(string animationName){
        int t = animationHash[animationName]-1;
        if(t<0){
            cout<<"[Animation.h] ERROR: Animation '"<<animationName<<"' does not exist\n";
            return 0;
        }
        return animationList.at(t).getNumberOfFrame();
    }

};


