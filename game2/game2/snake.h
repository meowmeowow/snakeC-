#ifndef snake_h
#define snake_h
using namespace std;
#include "thing.h"
#include <vector>


class Snake : public Thing {
public:
	static vector<Snake> snakes;

	static vector<int> turningPoint_x;
	static vector<int> turningPoint_y;

	int numberSnake;
	Snake();
	Snake(int x_, int y_, int dirX_, int dirY_, char self_,int numberSnake_);
	Snake(int x_, int y_, int dirX_, int dirY_, char self_);

	void addTurningPoint(int x, int y);
	int getNumber();
};
#endif /* snake_h */