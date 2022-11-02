#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "master.h"
#include "sdl_mastermind.h"

int tour = 0;

SDL_Color BLACK     = {0, 0, 0, 0};
SDL_Color WHITE     = {255, 255, 255, 90};
SDL_Color GREEN     = {0, 255, 0, 0};
SDL_Color RED       = {255, 0, 0, 0};
SDL_Color BLUE      = {0, 0, 255, 0};
SDL_Color YELLOW    = {200, 200, 0, 0};
SDL_Color ORANGE    = {255, 165, 0, 0};
SDL_Color CYAN      = {0, 255, 255, 0};

SDL_Color check[80]; 

// Thanks to StackOverflow :-)
void DrawRendererCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
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

void refreshWindow(SDL_Renderer * renderer)
{
    SDL_bool quit = SDL_FALSE;
    int proposition[4];
    int k = 0;
    int x = 7;
    combinaison c;
    SDL_Event event;
    SDL_Color defaultColors[6] = {RED, BLUE, YELLOW, GREEN, CYAN, ORANGE};

    while (!quit)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {  
            quit = SDL_TRUE;
        }else if (event.type == SDL_MOUSEBUTTONDOWN){
            SDL_Point p = {event.button.x, event.button.y};
            for (int i = 0; i < 6; i++){
                if ( circle[i].x - 20 <= p.x && p.x <= circle[i].x + 20
                    && circle[i].y - 20 <= p.y && p.y <= circle[i].y + 20 ){
                       if (tour < 40){
                            colors[tour] = defaultColors[i];
                            proposition[k] = i + 1;
                            k++;
                            tour++;
                            if ( tour %  4 == 0 )
                            {
                                k = 0;
                                c = compiler_proposition(proposition, solution);
                                for (int i = x - 7; i < x - 3; i++){
                                    if (c.bienp != 0)
                                    {
                                        sol_colors[i] = GREEN;
                                        c.bienp--;
                                    }
                                }
                                for (int i = x - 3; i < x; i++){
                                    if (c.malp != 0){
                                        sol_colors[i] = RED;
                                        c.malp--;
                                    }
                                }
                                x+=8;
                            }
                        }
                    }
            }
        }
        drawRendererGrid(renderer, colors);
        SDL_Delay(5);
        SDL_RenderPresent(renderer);
    }

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
            DrawRendererCircle(renderer, x, y, 15, colors[c_index]);
            c_index++;
        }
    }

    
    for (int y = NB_Y_MIN; y < NB_Y_MAX; y+= 37){
        for (int x = NB_X_MAX + 5; x < NB_X_MAX + 70; x+= 35){
            rect.x = x;
            rect.y = y;
            SDL_SetRenderDrawColor(renderer, sol_colors[i].r, sol_colors[i].g, sol_colors[i].b, sol_colors[i].a);
            SDL_RenderFillRect(renderer, &rect);
            i++;
            rect.x = x + 10;
            SDL_SetRenderDrawColor(renderer, sol_colors[i].r, sol_colors[i].g, sol_colors[i].b, sol_colors[i].a);
            SDL_RenderFillRect(renderer, &rect);
            i++;
            rect.x = x;
            rect.y = y + 10;
            SDL_SetRenderDrawColor(renderer, sol_colors[i].r, sol_colors[i].g, sol_colors[i].b, sol_colors[i].a);
            SDL_RenderFillRect(renderer, &rect); 
            i++;
            rect.x = x + 10;
            SDL_SetRenderDrawColor(renderer, sol_colors[i].r, sol_colors[i].g, sol_colors[i].b, sol_colors[i].a);
            SDL_RenderFillRect(renderer, &rect);
            i++;
        }
    }

    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    i = 0;
    for (int x = NB_X_MIN; x < NB_X_MAX + 120; x+= 60)
    {
        DrawRendererCircle(renderer, x, 395, 20, defaultColors[i]);
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

int main(){
    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;

    int germe = 10;
    initialiser_solution(solution,&germe);

    // Initialisation
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Error occur on SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    window   = SDL_CreateWindow("Mastermind", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (NULL == renderer)
    {
        fprintf(stderr, "Error occur on SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (0 != SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a)){
        fprintf(stderr, "Error occur on SDL_SetRenderDrawColor() : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Error occur on SDL_RendererClear() : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    //SDL_RenderPresent(renderer);
    
    initializeColors(colors);

    initializeSolColors(sol_colors);

    drawRendererGrid(renderer, colors);

    SDL_RenderPresent(renderer);
    refreshWindow(renderer);

    if (NULL != renderer){
        SDL_DestroyRenderer(renderer);
    }
    if (NULL != window){
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}