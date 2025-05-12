#include <stdio.h>
#include <SDL2/SDL.h>

const int width = 300;
const int height = 300;

enum Direction {
    up,
    left,
    right,
    down,
};

int main(){
    int x = width / 2;
    int y = height / 2;

    enum Direction direction = left;

	int frame = 0;
 
    if(SDL_Init(SDL_INIT_VIDEO) != 0) printf("init failed\n");

	SDL_Window *window = SDL_CreateWindow("Lanktons Ant", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (!window) printf("window failed\n");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) printf("renderer failed\n");
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) printf("texture failed\n");

	Uint32 frame_buffer[width * height];

    for (int i = 0; i < width * height; i++){
        frame_buffer[i] = 0xFFFFFFFF;
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
        if (!frame_buffer[y * width + x]){
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
