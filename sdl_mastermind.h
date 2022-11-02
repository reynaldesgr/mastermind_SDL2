#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef sdl_mastermind_h
#define sdl_mastermind_h


#define NB_X_MIN 20
#define NB_Y_MIN 20
#define NB_Y_MAX 390
#define NB_X_MAX 260

#define NB_COLORS 40
#define NB_SOL     8

SDL_Color colors[NB_COLORS];
SDL_Color sol_colors[NB_SOL];


struct point{
    int x;
    int y;
};
typedef struct point point;

point circle[4];

void drawRendererGrid(SDL_Renderer *renderer, SDL_Color colors[NB_COLORS]);
#endif