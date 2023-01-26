#include <iostream>
#include "wall.h"

using namespace std;




//Default Constructor
Wall::Wall(int x_, int y_, int dirX_, int dirY_, char self_) :Thing( x_,  y_,  dirX_,  dirY_,  self_) {
	walls.push_back(*this);
}

