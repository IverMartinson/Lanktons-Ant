#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

const int width = 800;
const int height = 800;

enum Direction {
    up,
    left,
    right,
    down,
};

int main(int arg_count, char* args[]){
	srand(time(NULL));

	int trace = 0;
	int randomize = 0;

	for (int arg = 1; arg < arg_count; arg++){
		if (strcmp(args[arg], "--trace")){
			randomize = 1;
		}
		
		else if (strcmp(args[arg], "--randomize")){
			trace = 1;
		}

		else {
			printf("unknown arg \"%s\"", args[arg]);
		}
	}

    int x = width / 2;
    int y = height / 2;

    enum Direction direction = left;

	int frame = 0;
 
    if(SDL_Init(SDL_INIT_VIDEO) != 0) printf("init failed\n");

	SDL_Window *window = SDL_CreateWindow("Lankton's Ant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (!window) printf("window failed\n");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) printf("renderer failed\n");
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) printf("texture failed\n");

	int ant_buffer[width * height];

	Uint32 frame_buffer[width * height];

    for (int i = 0; i < width * height; i++){
		if (randomize){
			ant_buffer[i] = rand() % 2;
		}
		else {
			ant_buffer[i] = 1;
		}
		
        if (trace || !randomize){
        	frame_buffer[i] = 0xFFFFFFFF;
		}
		else{
        	frame_buffer[i] = rand() % 2 * 0xFFFFFFFF;			
		}
    }

	int running = 1;
	while (running){
		frame++;
		
		SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    running = 0;
            }
        }

        x = (x + width) % width;
        y = (y + height) % height;

        // if black, go left
        // if white, go right
        if (!ant_buffer[y * width + x]){
            ant_buffer[y * width + x] = 1;

	        if (!trace)
	        	frame_buffer[y * width + x] = 0xFFFFFFFF; 
            
            switch (direction){
                case up:
                    x--;
                    direction = left;
                    break;
               
                case left:
                    y++;
                    direction = down;
                    break;
               
                case right:
                    y--;
                    direction = up;
                    break;
               
                case down:
                    x++;
                    direction = right;
                    break;
            }
        }
        else {
            ant_buffer[y * width + x] = 0;

        	if (!trace)
        		frame_buffer[y * width + x] = 0;
            
            switch (direction){
                case up:
                    x++;
                    direction = right;
                    break;

                case left:
                    y--;
                    direction = up;
                    break;
               
                case right:
                    y++;
                    direction = down;
                    break;
               
                case down:
                    x--;
                    direction = left;
                    break;
            }
        }

        if (trace)
        	frame_buffer[y * width + x] = 0; 

        if (frame % 10 != 0)
        	continue;

        SDL_UpdateTexture(texture, NULL, frame_buffer, width * sizeof(Uint32));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
	}

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
