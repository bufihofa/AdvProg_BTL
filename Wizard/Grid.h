#pragma once
#include <bits/stdc++.h>
using namespace std;
class Game;
class Bullet;
class NPC;
class Spike;
class Cell{
public:
    double x;
    double y;
    double delta = 0;
    bool have = false;
    Cell(){};
    Cell(double x, double y){
        this->x = x;
        this->y = y;
    }
};
class Grid{
private:
    int x;
    int y;

    double cols; // = w/cellSize;
    double rows; // = h/cellSize;
    Game* game;
    double cellSize;
    vector<vector<Cell*>> cell;
    vector<Cell> l;
    int du, dv;
    double dt;
    double xt[16];
    double yt[16];
public:
    int hg = 0;
    Grid(double x, double y, double w, double h, double cellSize, Game* game){
        this->rows = h/cellSize+1;
        this->cols = w/cellSize+1;
        this->game = game;
        this->cellSize = cellSize;
        createGrid();
        update(x ,y);

        double x225 = 1.0/sqrt(sqrt(2));
        double x45 = 1.0/sqrt(2);
        double y225 = sqrt(1-x225*x225);
        double y45 = sqrt(1-x45*x45);

        xt[0]=1; yt[0]=0;
        xt[1]=x225; yt[1]=-y225;
        xt[2]=x45; yt[2]=-y45;
        xt[3]=y225; yt[3]=-x225;

        xt[4]=0; yt[4]=-1;
        xt[5]=-y225; yt[5]=-x225;
        xt[6]=-x45; yt[6]=-y45;
        xt[7]=-x225; yt[7]=-y225;

        xt[8]=-1; yt[8]=0;
        xt[9]=-x225; yt[9]=y225;
        xt[10]=-x45; yt[10]=y45;
        xt[11]=-y225; yt[11]=x225;

        xt[12]=0; yt[12]=1;
        xt[13]=y225; yt[13]=x225;
        xt[14]=x45; yt[14]=y45;
        xt[15]=x225; yt[15]=y225;
    }
    void createGrid(){
        cell.resize(rows);
        for (int i = 0; i < rows; ++i) {
            cell[i].resize(cols);
            for(int j = 0; j < cols; ++j){
                cell[i][j] = new Cell();
            }
        }
    }
    void update(double x, double y);
    double getDistance(double x1, double x2, double y1, double y2){
        return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }
    double getDistance2(double x1, double x2, double y1, double y2){
        return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }
    void checkG(double u, double v, int k);
    void checkL(double u, double v, int k);
    void hashSpike(NPC* b);
    void hashSkill();
    void findPath(Spike* spike);
    void printMap(){

        for(int i=0; i<rows; ++i){
            for(int j = 0; j < cols; ++j){
                cout<<cell[i][j]->have<<" ";
            }
            cout<<"\n";
        }
    }
};
