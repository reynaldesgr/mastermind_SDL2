#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "master.h"
#include "sdl_mastermind.h"

int tour    = 0;

int      dk = 0;
int      dx = 7;

SDL_Color BLACK     = {  0,   0,   0,  0};
SDL_Color WHITE     = {255, 255, 255, 90};
SDL_Color GREEN     = {  0, 255,   0,  0};
SDL_Color RED       = {255,   0,   0,  0};
SDL_Color BLUE      = {  0,   0, 255,  0};
SDL_Color YELLOW    = {200, 200,   0,  0};
SDL_Color ORANGE    = {255, 165,   0,  0};
SDL_Color CYAN      = {  0, 255, 255,  0};

// Thanks to StackOverflow :-)
void drawRendererCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


int isVictoryOrLose(SDL_Window * window, SDL_Renderer * renderer){
    if (c.bienp == 4)
    {
        drawRendererGrid(renderer, colors);
        SDL_RenderPresent(renderer);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You're a master.", "Victoire !", window);
        return true;
    }
    if (tour == 40)
    {
        drawRendererGrid(renderer, colors);
        SDL_RenderPresent(renderer);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You lose.", "Perdu !", window);
        return true;
    }
    return false;
}

void checkSolution()
{ 
   dk = 0;
   c = compiler_proposition(proposition, solution);
   combinaison cbis = c;
    for (int i = dx - 7; i < dx - 3; i++){
        if (cbis.bienp != 0)
        {
           sol_colors[i] = GREEN;
           cbis.bienp--;
        }
    }
    for (int i = dx - 3; i < dx; i++){
        if (cbis.malp != 0)
        {
            sol_colors[i] = RED;
            cbis.malp--;
        }
    }
    dx+=8;

}

void checkColor(SDL_Point p, SDL_Color defaultColors[6])
{
    for (int i = 0; i < 6; i++){
                if ( circle[i].x - 20 <= p.x && p.x <= circle[i].x + 20
                    && circle[i].y - 20 <= p.y && p.y <= circle[i].y + 20 ){
                       if (tour < 40){
                            colors[tour] = defaultColors[i];
                            proposition[dk] = i + 1;
                            dk++;
                            tour++;
                            if ( tour %  4 == 0 )
                            {
                                checkSolution();
                            }
                        }
                    }
            }
}

void drawSmallSquare(SDL_Renderer * renderer, SDL_Rect rect, int index, int x, int y, int dx, int dy)
{
    rect.x = x + dx;
    rect.y = y + dy;
    SDL_SetRenderDrawColor(renderer, sol_colors[index].r, sol_colors[index].g, sol_colors[index].b, sol_colors[index].a);
    SDL_RenderFillRect(renderer, &rect);

}

void drawRendererGrid(SDL_Renderer *renderer, SDL_Color colors[NB_COLORS])
{
    SDL_Color defaultColors[6] = {RED, BLUE, YELLOW, GREEN, CYAN, ORANGE};
    int i                      = 0;
    int c_index                = 0;

    SDL_Rect rect;

    rect.h = 5;
    rect.w = 5;

    for (int y = NB_X_MIN; y < NB_Y_MAX; y+= 37){
        for (int x = NB_X_MIN; x < NB_X_MAX; x+= 60){
            drawRendererCircle(renderer, x, y, 15, colors[c_index]);
            c_index++;
        }
    }

    
    for (int y = NB_Y_MIN; y < NB_Y_MAX; y+= 37){
        for (int x = NB_X_MAX + 5; x < NB_X_MAX + 70; x+= 35){
            drawSmallSquare(renderer, rect, i, x, y,  0,  0);
            i++;
            drawSmallSquare(renderer, rect, i, x, y, 10,  0);
            i++;
            drawSmallSquare(renderer, rect, i, x, y,  0, 10);
            i++;
            drawSmallSquare(renderer, rect, i, x, y, 10, 10);
            i++;
        }
    }

    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    i = 0;
    for (int x = NB_X_MIN; x < NB_X_MAX + 120; x+= 60)
    {
        drawRendererCircle(renderer, x, 395, 20, defaultColors[i]);
        circle[i].x = x;
        circle[i].y = 395;
        i++;
    }
}


void initializeColors(SDL_Color colors[NB_COLORS])
{
    for (int i = 0; i < NB_COLORS; i++)
    {
        colors[i] = WHITE;
    }
}

void initializeSolColors(SDL_Color sol_color[80])
{
    for (int i = 0; i < 80; i++)
    {
        sol_color[i] = WHITE;
    }
}
