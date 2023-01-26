
#ifndef board_h
#define board_h
#include "thing.h"

using namespace std;
class Board {
private:
public:
	int height;
	int width;
	Thing* boardArray;
	Board();
	Board(int width, int height);
	~Board();
	string to_string();
	void changeDirection(int dirX, int dirY);
	void updateBoard();
	bool checkDeath();
	Thing* getBoardArray();
	int getHeight();
	int getWidth();

	
};
#endif /* board_h */