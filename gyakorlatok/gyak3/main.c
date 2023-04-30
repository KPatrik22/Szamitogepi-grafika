#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "line.h"
#include "color.h"

int main(){

    
    int counter = 0;
    Line vonal;
    Color szin;

    srand(time(NULL));
    

    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        printf("[Error] SDL initialization error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_bool valto = SDL_TRUE;

    while (valto)
    {
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if(counter == 0){
                    vonal.x1 = event.button.x;
                    vonal.y1 = event.button.y;
                    counter += 1;
                }else{
                    counter = 0;
                    vonal.x2 = event.button.x;
                    vonal.y2 = event.button.y;
                    szin.r = rand() % 255;
                    szin.g = rand() % 255;
                    szin.b = rand() % 255;                 
                }
                              
                    break;
            case SDL_KEYDOWN:
                valto = SDL_FALSE;
                break;
            
            default:
                break;
            }
            SDL_SetRenderDrawColor(renderer, szin.r, szin.g,szin.b, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, vonal.x1, vonal.y1, vonal.x2, vonal.y2); 
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    

    return 0;
    
}