#include "QTree.h"
#include "Game.h"
#include "Npc.h"
void Grid::hashSpike(NPC* b){
    int ax, ay, bx, by;
    int s = game->getBulletLoc().size();
    ax =   (b->getX()-x+b->vecX*8 - b->getR())/cellSize;
    ay =   (b->getY()-y+b->vecY*8 - b->getR())/cellSize;
    bx = ((b->getX()-x+b->vecX*8 + b->getR())/cellSize);
    by = ((b->getY()-y+b->vecY*8 + b->getR())/cellSize);

    for(int i = ay; i<=by; ++i){
        if(i>=0 && i<rows){
            for(int j = ax; j<=bx; ++j){
                if(j>=0 && j<cols){
                    if(cell[i][j]->delta == INT_MAX){
                        if(getDistance(b->getX()-x+b->vecX*8, cell[i][j]->x, b->getY()-y+b->vecY*8, cell[i][j]->y) < b->getR()*1.7){
                            cell[i][j]->delta = -1;
                        }

                    }
                }
            }
        }
    }
}
void Grid::hashSkill(){
    int ax, ay, bx, by;
    int s = game->getBulletLoc().size();
    Bullet* b;
    double temp, dX, dY;
    for(int i=0;i<s;++i){
        b = game->getBulletLoc().at(i);
        if(b->canDodge){
            temp = b->getDirectXY();
            dX = temp*(b->toX-b->getX())*5;
            dY = temp*(b->toY-b->getY())*5;

            ax =   (b->getX()+dX-x - b->getR())/cellSize;
            ay =   (b->getY()+dY-y - b->getR())/cellSize;
            bx = ((b->getX()+dX-x + b->getR())/cellSize);
            by = ((b->getY()+dY-y + b->getR())/cellSize);



            for(int i = ay; i<=by; ++i){
                if(i>=0 && i<rows){
                    for(int j = ax; j<=bx; ++j){
                        if(j>=0 && j<cols){
                            if(cell[i][j]->delta == INT_MAX){
                                if(getDistance(b->getX()+dX-x, cell[i][j]->x, b->getY()+dY-y, cell[i][j]->y) < b->getR()*2.5){
                                    cell[i][j]->delta = -1;
                                }

                            }
                        }
                    }
                }
            }
        }
    }
    //cell[rows/2][cols/2]->setZ(1);
    //Loang(rows/2, cols/2, 1);
    minx = rows/2;
    miny = cols/2;
    minz = INT_MAX;
    if(cell[minx][miny]->delta != -1) cell[minx][miny]->setZ(1);
    LoangZ(minx, miny, 1);
    Loang();

}
void Grid::checkG(int u, int v){
    if(cell[u][v]->delta > 0 && cell[u][v]->delta < dt || (cell[u][v]->delta == dt && rand()%4 == 0)){
        dt = cell[u][v]->delta;
        du = u;
        dv = v;
    }
}
void Grid::findPath(Spike* spike){
    if(spike->distanceBetween(game->p) < 20){
        spike->update(spike->getX(), spike->getY());
        return;
    }

    int j = (spike->getX()-x)/cellSize;
    int i = (spike->getY()-y)/cellSize;

    if(i<1 || i>=rows-1 || j<1 || j>=cols-1){
        spike->update(game->p->getX(), game->p->getY()+10);
        return;
    }
    du = i;
    dv = j;
    dt = INT_MAX-1;

    checkG(i+1, j+1);
    checkG(i+1, j);
    checkG(i+1, j-1);
    checkG(i, j+1);
    checkG(i, j-1);
    checkG(i-1, j+1);
    checkG(i-1, j);
    checkG(i-1, j-1);

    if(i==du && j == dv){
        spike->update(game->p->getX(), game->p->getY()+10);
        return;
    }
    if(getDistance(spike->toX, spike->getX()+(dv-j)*cellSize , spike->toY,spike->getY()+(du-i)*cellSize)>cellSize/1.5)
        spike->setToXY(spike->getX()+(dv-j)*cellSize + game->p->vecX*(rand()%3 + 2)*(rand()%3 - 1), spike->getY()+(du-i)*cellSize + game->p->vecY*(rand()%3 + 2)*(rand()%3 - 1));

    spike->update(spike->toX , spike->toY);
    //spike->update(spike->getX()+(dv-j)*cellSize , spike->getY()+(du-i)*cellSize );

}
