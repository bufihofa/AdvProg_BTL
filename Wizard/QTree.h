#pragma once
#include <bits/stdc++.h>
using namespace std;
class Game;
class Bullet;
class NPC;
class Spike;
class Cell{
public:
    int x;
    int y;
    double delta = 0;
    bool ktra = true;
    void setZ(double z){
        delta = z;
    }
    Cell(){};
    Cell(int x, int y, double delta){
        this->x = x;
        this->y = y;
        this->delta = delta;
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
    bool findC = false;
    int minx, miny, minz;
public:
    int coa = 0;
    int ia = 0;
    Grid(double x, double y, double w, double h, double cellSize, Game* game){

        this->rows = h/cellSize+1;
        this->cols = w/cellSize+1;
        this->game = game;
        this->cellSize = cellSize;
        createGrid();
        update(x ,y);



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
    void update(double x, double y){
        this->x = x-cellSize/2;
        this->y = y-cellSize/2;

        for(int i=0; i<rows; ++i){
            for(int j = 0; j < cols; ++j){
                cell[i][j]->x = j*cellSize + cellSize/2;
                cell[i][j]->y = i*cellSize + cellSize/2;
                cell[i][j]->delta = INT_MAX;
                cell[i][j]->ktra = true;
            }
        }
    }
    double getDistance(double x1, double x2, double y1, double y2){
        return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }


    int f(double F){
        if(F-int(F)>0) return F+1;
        return F;
    }
    void checkG(int u, int v);
    void hashSpike(NPC* b);
    void hashSkill();
    void findPath(Spike* spike);

    void LoangZ(int x, int y, int z){
        if(cell[x][y]->delta == -1 && cell[x][y]->ktra && x>minx-5 && x<minx+5 && y>miny-5 && y<miny+5){
            cell[x][y]->ktra = false;
            cell[x][y]->setZ(INT_MAX);
            LoangZ(x+1, y, z+1);
            LoangZ(x-1, y, z+1);
            LoangZ(x, y+1, z+1);
            LoangZ(x, y-1, z+1);

            LoangZ(x+1, y+1, z+1);
            LoangZ(x-1, y-1, z+1);
            LoangZ(x-1, y+1, z+1);
            LoangZ(x+1, y-1, z+1);
        }
    }
    void checkL(int x, int y, double z){
        if(cell[x][y]->delta != -1 && z < cell[x][y]->delta && x>0 && x<rows-1 && y>0 && y<cols-1){
            cell[x][y]->setZ(z);
            l.push_back(Cell(x, y, z));
        }

    }
    void Loang(){
        cell[minx][miny]->setZ(1);
        l.push_back(Cell(minx, miny, 1));
        while(ia<l.size()){

            checkL(l[ia].x+1, l[ia].y, l[ia].delta+1);
            checkL(l[ia].x, l[ia].y+1, l[ia].delta+1);
            checkL(l[ia].x-1, l[ia].y, l[ia].delta+1);
            checkL(l[ia].x, l[ia].y-1, l[ia].delta+1);

            checkL(l[ia].x+1, l[ia].y+1, l[ia].delta+1.41421);
            checkL(l[ia].x-1, l[ia].y+1, l[ia].delta+1.41421);
            checkL(l[ia].x-1, l[ia].y-1, l[ia].delta+1.41421);
            checkL(l[ia].x+1, l[ia].y-1, l[ia].delta+1.41421);
            ia++;
        }

        ia = 0;
        l.clear();
    }
    void printMap(){
        for(int i=0;i<rows;++i){
            for(int j = 0;j<cols;++j){
                if(cell[i][j]->delta == -1) cout<<"# "; else cout<<int(cell[i][j]->delta) % 10<<" ";
            }
            cout<<endl;
        }
    }
};
