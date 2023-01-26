#ifndef controller_h
#define controller_h
using namespace std;
#include "board.h"


class Controller {
public:
	int turn;
	bool win = false;
	Board b;
	Controller();
	Controller(bool a);
	~Controller();
	void incrimentTime();
	string to_string();
	void changeDirection(int dirX_, int dirY_);
	bool checkDeath();
	bool checkApple();

	void changeXY(int x, int y, Thing a);
	bool update(int dirX_, int dirY_);
	void newApplePosition();
	void newApplePosition(Thing* boardArray);
		void moveSnake();

		bool checkWin();
		bool getWin();
		void updateBoard();
		Board getBoard();

};
#endif /* controller_h */