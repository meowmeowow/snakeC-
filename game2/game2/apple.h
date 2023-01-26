#ifndef apple_h
#define apple_h
using namespace std;
#include "thing.h"
#include <vector>

class Apple : public Thing {
public:
	static vector<Apple> apples;
	Apple(int x_, int y_, int dirX_, int dirY_, char self_);
};
#endif /* apple_h */