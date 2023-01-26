#include <iostream>
#include <SDL.h>
#include <stdio.h>

#include "controller.h"

//Using SDL, standard IO, and strings

//Screen dimension constants
const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 450;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);
int SPRITE_SIZE = 45;
int dirX;
int dirY;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;


SDL_Surface *temp, *wall, *snake, *apple, *blank;
SDL_Rect rcWall, rcSnake, rcApple , rcBlank;
Controller a;
////////////////////////////////////////////////////
using namespace std;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}



	return success;
}
////////////////////////////////////////////////////

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//temp = SDL_LoadBMP("right.bmp");
	wall = loadSurface("right.bmp");
	snake = loadSurface("down.bmp");
	apple = loadSurface("left.bmp");
	blank = loadSurface("up.bmp");

	return(true);
	//Load default surface

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}



	return success;
}
////////////////////////////////////////////////////
void close()
{
	//Deallocate surfaces
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
////////////////////////////////////////////////////

SDL_Surface* loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

void displayScreen(Controller a) {
	Thing* board = a.getBoard().getBoardArray();
	int height = a.getBoard().getHeight();
	int width = a.getBoard().getWidth();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (board[i * height + j].getSelf() == 'b') {
				//wall
				rcWall.x = j * SPRITE_SIZE;
				rcWall.y = i * SPRITE_SIZE;
				SDL_BlitSurface(wall, NULL, gScreenSurface, &rcWall);

			}
			else if (board[i * height + j].getSelf() == 'c') {
				//snake
				rcSnake.x = j * SPRITE_SIZE;
				rcSnake.y = i * SPRITE_SIZE;
				SDL_BlitSurface(snake, NULL, gScreenSurface, &rcSnake);

			}
			else if (board[i * height + j].getSelf() == 'd') {
				//apple
				rcApple.x = j * SPRITE_SIZE;
				rcApple.y = i * SPRITE_SIZE;
				SDL_BlitSurface(apple, NULL, gScreenSurface, &rcApple);

			}
			else {
				//set black wall 
				rcBlank.x = j * SPRITE_SIZE;
				rcBlank.y = i * SPRITE_SIZE;
				SDL_BlitSurface(blank, NULL, gScreenSurface, &rcBlank);

			}
		}
	}


}

Uint32 callback(Uint32 interval, void* param)
{

	///
	bool lose = a.update(dirX, dirY);
	a.incrimentTime();
	if (lose == true) {
		cout << "you lost oh no :( \n";
		close();
	}
	else if (a.getWin() == true) {
		cout << "you won yay! \n";
		close();
	}
	displayScreen(a);

	return interval;
}
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			a = Controller(true);
			string prevMove = "";
			string move;
			dirX = 0;
			dirY = 0;
			cout << a.to_string();
			//While application is running

			SDL_TimerID timerID = SDL_AddTimer(0.3 * 1000, callback, NULL);



			while (!quit)
			{

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
							//Select surfaces based on key press
							switch (e.key.keysym.sym)
							{
								//movment :)
							case SDLK_UP:
								dirY = -1;
								dirX = 0;


								//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;

							case SDLK_DOWN:
								dirY = 1;
								dirX = 0;

								//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;

							case SDLK_LEFT:
								dirY = 0;
								dirX = -1;

								//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;

							case SDLK_RIGHT:
								dirY = 0;
								dirX = 1;

								//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;

							default:
								//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
							}
					}
					//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
				}


				//Apply the current image
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

			}
			SDL_RemoveTimer(timerID);

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


