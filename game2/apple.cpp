#include <iostream>
#include "apple.h"

using namespace std;




//Default Constructor
Apple::Apple(int x_, int y_, int dirX_, int dirY_, char self_) :Thing( x_,  y_,  dirX_,  dirY_,self_) {
	apples.push_back(*this);

}

