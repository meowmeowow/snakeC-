#ifndef wall_h
#define wall_h
using namespace std;
#include "thing.h"

#include <vector>
class Wall: public Thing {
public:
	static vector<Wall> walls;
	Wall(int x_, int y_, int dirX_, int dirY_, char self_);
};
#endif /* wall_h */