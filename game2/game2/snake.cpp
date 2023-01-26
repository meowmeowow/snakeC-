#include <iostream>
#include "snake.h"

using namespace std;




//Default Constructor
Snake::Snake() {
	numberSnake = -1;
}
Snake::Snake(int x_, int y_, int dirX_, int dirY_, char self_, int numberSnake_) :Thing( x_,  y_,  dirX_,  dirY_,self_) {
	numberSnake = numberSnake_;

	snakes.push_back(*this);


}
Snake::Snake(int x_, int y_, int dirX_, int dirY_, char self_) :Thing(x_, y_, dirX_, dirY_, self_) {

	snakes.insert(snakes.begin(), *this);



}

void Snake::addTurningPoint(int x, int y) {
	turningPoint_x.push_back(x);
	turningPoint_y.push_back(y);

}

int Snake::getNumber() {
	return(numberSnake);
}

