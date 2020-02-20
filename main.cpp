#include <math.h>
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480

int main(int argc, char* args[])
{
	SDL_Window* Window;
	SDL_Renderer* Renderer;

	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return -1;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return -1;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return -1;
	}

	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);

	//Draw some geometry
	int n = 0;
	const int cx = WINDOW_WIDTH >> 1,
			  cy = WINDOW_HEIGHT >> 1;
	SDL_Rect rc = { 0, cy, 10, 10 };	//x, y, w, h
	float alpha;
	while (n < 360)
	{	
		alpha = n * M_PI / 180.0f;
		rc.x += 17;

		SDL_SetRenderDrawColor(Renderer, n*0.7f, 192, 0, 255);
		SDL_RenderFillRect(Renderer, &rc);

		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(Renderer, cx, cy, cx + cy * cos(alpha), cy - cy * sin(alpha));

		//Wait a specified number of milliseconds
		SDL_Delay(100);
		
		//Update screen
		SDL_RenderPresent(Renderer);
		
		n += 10;
	}
	SDL_Delay(1000);

	//Clean up all SDL initialized subsystems
	SDL_Quit();

	return 0;
}