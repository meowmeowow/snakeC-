#include <iostream>
#include "controller.h"
#include <vector>
#include "wall.h"
#include "apple.h"
#include "snake.h"
#include<cstdlib>
#include <time.h>

using namespace std;


vector<Snake> Snake::snakes;
vector<int> Snake::turningPoint_x;
vector<int> Snake::turningPoint_y;

vector<Wall> Wall::walls;
vector<Apple> Apple::apples;


//Default Constructor
Controller::Controller(bool a)
{
    turn = 0;
    b = Board(10,10);
    srand((unsigned)time(NULL));


}
Controller::Controller()
{


}

Controller::~Controller()
{
    //delate board
}
void Controller::incrimentTime() {
    turn++;
}
string Controller::to_string() {
    return(b.to_string());
}

void Controller::changeDirection(int dirX_, int dirY_) {
    //change direction of snaky head + add input for this
    Thing* boardArray = b.getBoardArray();
    Snake::snakes.front().setDir(dirX_, dirY_);


}
void Controller::changeXY(int x, int y, Thing a) {
    //change direction of snaky head + add input for this
    Thing* boardArray = b.getBoardArray();
    a.setXY(x, y);


}
bool Controller::checkDeath() {
    //check if snake head is touching itself or wall 
    //getBoardArray
    //before movment
    Thing* boardArray = b.getBoardArray();

    Snake head = Snake::snakes.front();
    int height = b.getHeight();
    if (head.getDirX() != 0) {
        //sideways
        
        if (boardArray[head.getY() * height + head.getX() + head.getDirX()].getSelf() == 'b' || boardArray[head.getY() * height + head.getX() + head.getDirX()].getSelf() == 'c') {
            return(true);
        }
    }
    else if (head.getDirY() != 0) {
        //up
        if (boardArray[(head.getY()+head.getDirY()) * height + head.getX()].getSelf() == 'b' || boardArray[(head.getY() + head.getDirY()) * height + head.getX()].getSelf() == 'c') {
            return(true);
        }
    }

    return(false);
}
bool Controller::checkApple() {
    //check if snake head is touching itself or wall 
    //getBoardArray
    //before movment
    Thing* boardArray = b.getBoardArray();

    Snake head = Snake::snakes.front();
    int height = b.getHeight();
    if (head.getDirX() != 0) {
        //sideways

        if (boardArray[head.getY() * height + head.getX() + head.getDirX()].getSelf() == 'd') {
            return(true);
        }
    }
    else if (head.getDirY() != 0) {
        //up
        if (boardArray[(head.getY() + head.getDirY()) * height + head.getX()].getSelf() == 'd') {
            return(true);
        }
    }

    return(false);
}


void Controller::newApplePosition(Thing * boardArray) {
    int xx=0;
    int yy=0;
    while (1==1) {
        xx = (rand() % b.getWidth());
        yy = (rand() % b.getHeight());
        if (boardArray[yy * b.getHeight() + xx].getSelf() == '-'){
            break;
        }

    }
    Apple::apples.front().setXY(xx, yy);
}

void Controller::moveSnake() {

    //Thing* boardArray = b.getBoardArray();

    //for (int i = 0; i < Snake::snakes.size(); i++) {

        
    //}
    Snake::snakes.pop_back();
    Snake s = Snake(Snake::snakes.front().getX() + Snake::snakes.front().getDirX(), Snake::snakes.front().getY() + Snake::snakes.front().getDirY(), Snake::snakes.front().getDirX(), Snake::snakes.front().getDirY(), 'c');
}
bool Controller::checkWin() {
    Thing* boardArray = b.getBoardArray();
    if (Snake::snakes.size() + Apple::apples.size() + Wall::walls.size() == b.getHeight() * b.getWidth()) {
        return(true);
    }
    return(false);
}

bool Controller::getWin() {
    return(win);
}
void Controller::updateBoard() {
    int height = b.getHeight();
    int width = b.getWidth();
    Thing* boardArray = b.getBoardArray();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            boardArray[i * height + j] = Thing();
        }
    }


    for (int i = 0; i < Snake::snakes.size(); i++) {
        boardArray[Snake::snakes[i].getY() * height + Snake::snakes[i].getX()] = Snake::snakes[i];
    }
    for (int i = 0; i < Wall::walls.size(); i++) {
        boardArray[Wall::walls[i].getY() * height + Wall::walls[i].getX()] = Wall::walls[i];
    }
    for (int i = 0; i < Apple::apples.size(); i++) {
        boardArray[Apple::apples[i].getY() * height + Apple::apples[i].getX()] = Apple::apples[i];
    }
}
bool Controller::update(int dirX_, int dirY_) {
    //before movment
    //update board with new direction


    Thing* boardArray = b.getBoardArray();

    if (dirX_ == 0 && dirY_ == 0) {
        return(false);
    }

    changeDirection(dirX_, dirY_);

    if (checkDeath() == true) {
        return(true);//DEATH
    }

    //check win
    if (checkWin() == true) {
        win = true;
        return false;
    }

    bool app = checkApple();
    //move everything

    moveSnake();



    if (app == true) {
        //change apple position
        newApplePosition(boardArray);
        // add new at end 
        Snake s = Snake(Snake::snakes.back().getX() - Snake::snakes.back().getDirX(), Snake::snakes.back().getY() - Snake::snakes.back().getDirY(), Snake::snakes.back().getDirX(), Snake::snakes.back().getDirY(), 'c', Snake::snakes.back().getNumber() + 1);
        //Snake::snakes.push_back(s);
    }
    //update board
    updateBoard();

    

    return(false);//nothing happens



}
Board Controller::getBoard() {
    return(b);
}