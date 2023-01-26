
#ifndef thing_h
#define thing_h

using namespace std;
class Thing {
public:
	int x;
	int y;
	int dirX;
	int dirY;
	char self;
	Thing();
	Thing(int x_, int y_, int dirX_, int dirY_, char self_);
	~Thing();
	char getSelf();
	int getX();
	int getY();

	int getDirX();
	int getDirY();


	void setDir(int dirX_, int dirY_);
	void setXY(int x_, int y_);

};
#endif /* Thing_h */