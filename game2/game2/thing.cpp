#include <iostream>
#include "thing.h"

using namespace std;




    //Default Constructor
Thing::Thing() {
    x = -1;
    y = -1;
    dirX = 0;
    dirY = 0;
    self = '-';

}
Thing::Thing(int x_, int y_, int dirX_, int dirY_, char self_)
    {
    x = x_;
    y = y_;
    dirX = dirX_;
    dirY = dirY_;
    self = self_;
    }

Thing::~Thing()
    {
        //delate board
    x = -1;
    y = -1;
    dirX = 0;
    dirY = 0;
    self = 'a';
    }
char Thing::getSelf() {
    return(self);
}
void Thing::setDir(int dirX_, int dirY_) {
    this->dirX = dirX_;
    this->dirY = dirY_;

}
void Thing::setXY(int x_, int y_) {
    x = x_;
    y = y_;

}

int Thing::getDirX() {
    return dirX;
}
int Thing::getDirY() {
    return dirY;
}
int Thing::getX() {
    return x;
}
int Thing::getY() {
    return y;
}