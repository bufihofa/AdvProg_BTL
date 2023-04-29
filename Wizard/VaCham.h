#pragma once
#include <bits/stdc++.h>
using namespace std;

int dem = 0;
class QuadtreeNode {
public:
    int level;
    float x, y; // Tọa độ trung tâm của ô
    float size; // Kích thước của ô
    vector<NPC*> objects; // Danh sách các đối tượng trong ô
    QuadtreeNode* children[4]; // Con trỏ đến các nút con của nút hiện tại

    QuadtreeNode(int level, float x, float y, float size) : level(level), x(x), y(y), size(size) {
        for (int i = 0; i < 4; i++) {
            children[i] = nullptr;
        }
    }

    ~QuadtreeNode() {
        for (int i = 0; i < 4; i++) {
            delete children[i];
        }
    }

    // Phương thức thêm đối tượng vào nút
    void addObject(NPC* obj) {
        objects.push_back(obj);
        //cout<<"add\n";
    }

    // Phương thức kiểm tra xem đối tượng có nằm trong nút không
    bool contains(NPC* obj) {
        return obj->getX() >= x - size && obj->getX() < x + size &&
               obj->getY() >= y - size && obj->getY() < y + size;
    }

    // Phương thức chia nút thành 4 nút con
    void subdivide() {
        children[0] = new QuadtreeNode(level + 1, x - size / 2.0f, y - size / 2.0f, size / 2.0f);
        children[1] = new QuadtreeNode(level + 1, x + size / 2.0f, y - size / 2.0f, size / 2.0f);
        children[2] = new QuadtreeNode(level + 1, x - size / 2.0f, y + size / 2.0f, size / 2.0f);
        children[3] = new QuadtreeNode(level + 1, x + size / 2.0f, y + size / 2.0f, size / 2.0f);
    }

    // Phương thức thêm đối tượng vào cây

    void add(NPC* obj) {
        if (!contains(obj)) {
            return;
        }
        if (children[0] != nullptr) {
            for (int i = 0; i < 4; i++) {
                children[i]->add(obj);
            }
        }
        else {
            addObject(obj);
            if (objects.size() > 10 && level < 3) {
                subdivide();
                for (NPC* obj : objects) {
                    for (int i = 0; i < 4; i++) {
                        children[i]->add(obj);
                    }
                }
                objects.clear();
            }
        }
    }

    // Phương thức kiểm tra va chạm giữa các đối tượng trong nút
    void handleCollisions() {
        for (int i = 0; i < objects.size(); i++) {
            if(!objects[i]->isEnemy){
                for (int j = 0; j < objects.size(); j++) {
                    if(objects[j]->isEnemy){
                        dem++;
                        if (collide(objects[i], objects[j])) {
                            objects[j]->damaged(objects[i]);
                            //cout<<level<<" ";
                        }
                    }
                }
            }
        }


        if (children[0] != nullptr) {
            for (int i = 0; i < 4; i++) {
                children[i]->handleCollisions();
            }
        }
    }


    // Phương thức xoá toàn bộ đối tượng trong cây
    void clear() {
        for (int i = 0; i < 4; i++) {
            if (children[i] != nullptr) {
                children[i]->clear();
                delete children[i];
                children[i] = nullptr;
            }
        }
        objects.clear();
    }

    // Phương thức kiểm tra va chạm giữa 2 đối tượng
    /*
    bool collide(NPC* obj1, NPC* obj2) {
        float dx = obj1->getX() - obj2->getX();
        float dy = obj1->getY() - obj2->getY();
        float dist = sqrt(dx * dx + dy * dy);
        return sqrt(dx * dx + dy * dy) < obj1->getR() + obj2->getR();
    }
    */
    bool collide(NPC* obj1, NPC* obj2) {
        return sqrt((obj1->getX() - obj2->getX()) * (obj1->getX() - obj2->getX()) + (obj1->getY() - obj2->getY()) * (obj1->getY() - obj2->getY())) < obj1->getR() + obj2->getR();
    }
};

class Quadtree {
private:
    QuadtreeNode* root; // Nút gốc của cây Quadtree

public:
    Quadtree();
    Quadtree(float x, float y, float size) {
        root = new QuadtreeNode(1, x, y, size);
    }

    ~Quadtree() {
        delete root;
    }
    void update(double x, double y, double size){
        root = new QuadtreeNode(1, x, y, size);

    }
    // Phương thức thêm đối tượng vào cây Quadtree
    void add(NPC* obj) {
        root->add(obj);
    }

    // Phương thức xử lí va chạm giữa các đối tượng trong cây Quadtree
    void handleCollisions() {
        root->handleCollisions();
    }

    // Phương thức xoá toàn bộ đối tượng trong cây Quadtree
    void clear() {
        cout<<dem<<"\n";
        root->clear();
        delete root;
        dem = 0;
    }
};
