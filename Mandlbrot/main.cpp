#include "SDL.h"
#include <Windows.h>
#include <string>
#include <cmath>

int WIDTH = 800;
int HEIGHT = 800;

long double min = -2.84;
long double max = 1.0;

long double factor = 1.0;

int MAX_ITERATIONS = 500;

long double map(long double value, long double input_min, long double input_max, long double output_min, long double output_max) 
{
	return ((value - input_min) * (output_max - output_min) / (input_max - input_min) + output_min);
}

int main(int argc, char* argv[]) 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	//SDL_CreateWindowAndRenderer(2560, 1440,0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

	int count = 0;

	while (1)
	{
		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.93496723123;
		MAX_ITERATIONS += 5;

		if (count > 30) {
			MAX_ITERATIONS *= 1.05;
		}

		SDL_RenderPresent(renderer);

		for (int x = 0; x < WIDTH; x++){// x = a

			if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
				return 0;
			if (GetKeyState('Q') & 0x8000)
				return 0;

			for (int y = 0; y < HEIGHT; y++) // y = b
			{
				long double a = map(x , 0, WIDTH, min, max);
				long double b = map(y, 0, HEIGHT, min, max);

				long double a_initial = a;
				long double b_initial = b;

				int n = 0;

				for(int i = 0; i < MAX_ITERATIONS; i++){
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;

					a = a1 + a_initial;
					b = b1 + b_initial;

					if (sqrt(a * a + b * b) > 2){
						break;
					}

					n++;
				}

				int bright = map(n, 0, MAX_ITERATIONS, 0, 255);

				if (n == MAX_ITERATIONS){

					bright = 0;
					
				}

				int red = bright * bright;
				int green = bright * 4;
				int blue = bright*2;


				SDL_SetRenderDrawColor(renderer, bright, green, blue, 255);
				SDL_RenderDrawPointF(renderer, x, y);
				
			}
			
		}
		//SDL_Surface* sshot = SDL_GetWindowSurface(window);
		//SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		//std::string file = std::to_string(count) + ".bmp";
		//SDL_SaveBMP(sshot, file.c_str());
		//SDL_FreeSurface(sshot);

		count++;
		
	}

	return 0;
}