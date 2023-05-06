#include "Grid.h"
#include "Game.h"
#include "Npc.h"
void Grid::update(double x, double y){
    this->x = x-cellSize/2;
    this->y = y-cellSize/2;
    for(int i=0; i<rows; ++i){
        for(int j = 0; j < cols; ++j){
            cell[i][j]->x = j*cellSize + cellSize/2;
            cell[i][j]->y = i*cellSize + cellSize/2;
            cell[i][j]->have = false;
            cell[i][j]->delta = getDistance(x+cell[i][j]->x, game->p->getX(), y+cell[i][j]->y, game->p->getY());
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
            if(b->vecX+b->vecY != 0){
                dX = b->vecX*25;
                dY = b->vecY*25;

                ax =   (b->getX()+dX-x - b->r*2)/cellSize;
                ay =   (b->getY()+dY-y - b->r*2)/cellSize;
                bx = ((b->getX()+dX-x + b->r*2)/cellSize);
                by = ((b->getY()+dY-y + b->r*2)/cellSize);

                for(int i = ay; i<=by; ++i){
                    if(i>=0 && i<rows){
                        for(int j = ax; j<=bx; ++j){
                            if(j>=0 && j<cols){
                                if(getDistance2(b->getX()+dX-x, cell[i][j]->x, b->getY()+dY-y, cell[i][j]->y) < b->r*b->r*1.8){
                                    cell[i][j]->delta = -1;
                                }

                            }
                        }
                    }
                }
            }

            ax =   (b->getX()+dX-x - b->r*2)/cellSize;
            ay =   (b->getY()+dY-y - b->r*2)/cellSize;
            bx = ((b->getX()+dX-x + b->r*2)/cellSize);
            by = ((b->getY()+dY-y + b->r*2)/cellSize);

            for(int i = ay; i<=by; ++i){
                if(i>=0 && i<rows){
                    for(int j = ax; j<=bx; ++j){
                        if(j>=0 && j<cols){
                            if(getDistance2(b->getX()+dX-x, cell[i][j]->x, b->getY()+dY-y, cell[i][j]->y) < b->r*b->r*1.8){
                                cell[i][j]->delta = -1;
                            }

                        }
                    }
                }
            }
        }
    }

}
void Grid::checkG(double j, double i, int k){
    int u = i/cellSize;
    int v = j/cellSize;
    if(u<1 || u>=rows-1 || v<1 || v>=cols-1){
        du = -2;
        return;
    }
    if(cell[u][v]->delta > 0 && getDistance2(j, 910, i, 610) < dt && !cell[u][v]->have){
        dt = getDistance2(j, 910, i, 610);
        du = k;
    }
}

void Grid::findPath(Spike* spike){
    dv = spike->distanceBetween(game->p);
    if(dv < 25){
        spike->update(spike->getX(), spike->getY());
        du = ((spike->getY()-y)/cellSize);
        dt = ((spike->getX()-x)/cellSize);
        cell[int(du)][int(dt)]->have = true;
        return;
    }
    du = -1;
    dt = INT_MAX;

    for(int k = 0; k < 16; ++k){
        checkG(spike->getX() + 15*xt[k] * spike->getSpeed()-x, spike->getY() +15*yt[k] * spike->getSpeed()-y, k);
    }

    if(du == -2){
        spike->update(game->p->getX(), game->p->getY());
    }
    else if(du>=0){
        spike->update(spike->getX() + xt[du] * spike->getSpeed(), spike->getY() + yt[du] * spike->getSpeed());
    }
    du = ((spike->getY()-y)/cellSize);
    dt = ((spike->getX()-x)/cellSize);
    if(du>1 && du<rows-1 && dt>1 && dt<cols-1) cell[int(du)][int(dt)]->have = true;
}
