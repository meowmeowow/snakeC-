#include <iostream>
using namespace std;
#include <cstdlib>
#include "board.h"
#include "wall.h"
#include "apple.h"
#include "snake.h"


Board::Board() {

}
    Board::Board(int width_, int height_)
    { 
        width = width_;
        height = height_;
        boardArray= new Thing[height*width];


        Thing temp;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height-1) {
                    temp = Wall(i,j,0,0,'b');
                    boardArray[i * height + j] = temp;
                }
                else if (j == 0 || j == width-1) {
                    temp = Wall(i,j,0,0,'b');
                    boardArray[i * height + j] = temp;
                }
            }
        }
        //wrong
        boardArray[36] = Snake(6, 3, 0, 0, 'c', 0);
        boardArray[35] = Snake(5, 3, 0, 0, 'c', 0);
        boardArray[34] = Snake(4, 3, 0, 0, 'c', 0);
        boardArray[22] = Apple(2, 2, 0, 0,'d');


    }
    Board::~Board()
    {
        //delate board
    }

    string Board::to_string() {
        string a = "";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                a += boardArray[i * height + j].getSelf();            
            }
            a += "\n";
        }
        return(a);

    }


    void Board::updateBoard() {
        //go through arrays and update ENTIRE THINGY HAHAHAH<3


    }


    Thing* Board::getBoardArray() {
        return(boardArray);
    }

    int Board::getHeight() {
        return(height);
    }

    int Board::getWidth() {
        return(width);
    }