#ifndef ANIMATION_H
#define ANIMATION_H

#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_utils.h"
#include "Entity.h"

using namespace std;


class AnimationLoad{
private:
    vector<SDL_Texture*> frameList;
    int numberOfFrame;
    int speedOfFrame;
    int h, w;
    SDL_Renderer* renderer;
public:
    AnimationLoad(){}
    AnimationLoad(string path,int numberOfFrame, int speedOfFrame, SDL_Renderer* renderer){

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
    void clearAnimationSave(){
        for(int i=0;i<numberOfFrame;++i){
            SDL_DestroyTexture(frameList[i]);
            //image = NULL;
        }
        renderer = NULL;
    }
    SDL_Texture* getFrame(int i){
        return frameList.at(i);
    }
};

class AnimationObject{
private:
    vector<AnimationLoad> animationLoadList;
    map<string, int> animationHash;
    double time = 0;
    Entity* animationPen = new Entity();
public:
    AnimationObject(){}

    void loadAnimation(string animationName, string path, int numberOfFrame, int speedOfFrame, SDL_Renderer* renderer){
        if(animationHash[animationName] > 0){
            cout<<"[Animation.h] Error: Animation '"<<animationName<<"': load failed - animationName is duplicated\n";
            return;
        }
        animationLoadList.push_back(AnimationLoad(path, numberOfFrame, speedOfFrame, renderer));
        animationHash[animationName] = animationLoadList.size();
        cout<<"[Animation.h] Loaded Animation '"<<animationName<<"'\n";

    }
    SDL_Texture* getAnimation(string animationName, int frame){
        int t = animationHash[animationName]-1;
        return animationLoadList.at(t).getFrame(frame);
    }
    SDL_Texture* getAnimationWithID(int id, int frame){
        return animationLoadList.at(id).getFrame(frame);
    }
    int convertNameToID(string name){
        return (animationHash[name]-1);
    }
    int getMaxFrameAnimation(string animationName){
        int t = animationHash[animationName]-1;
        return animationLoadList.at(t).getNumberOfFrame();
    }

};


#endif //ANIMATION.H
