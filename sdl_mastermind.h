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

extern SDL_Color BLACK;
extern SDL_Color WHITE;
extern SDL_Color GREEN;
extern SDL_Color RED;
extern SDL_Color BLUE;
extern SDL_Color YELLOW;
extern SDL_Color ORANGE;
extern SDL_Color CYAN;

extern int tour;
extern int dx;
extern int dk;

int   proposition[4];

SDL_Color check[80];


SDL_Color colors[NB_COLORS];
SDL_Color sol_colors[NB_SOL];


struct point{
    int x;
    int y;
};
typedef struct point point;

point circle[4];
combinaison c;

void drawRendererCircle         (SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void drawSmallSquare            (SDL_Renderer * renderer, SDL_Rect rect, int index, int x, int y, int dx, int dy);
void drawRendererGrid           (SDL_Renderer *renderer, SDL_Color colors[NB_COLORS]);

void checkSolution              (void);
void checkColor                 (SDL_Point p, SDL_Color defaultColors[6]);

void initializeColors           (SDL_Color colors[NB_COLORS]);
void initializeSolColors        (SDL_Color sol_color[80]);

int isVictoryOrLose             (SDL_Window * window, SDL_Renderer * renderer);

#endif