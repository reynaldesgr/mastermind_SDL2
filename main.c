#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sys/types.h>
#include <unistd.h>

#include "master.h"
#include "sdl_mastermind.h"

void refreshWindow(SDL_Renderer * renderer, SDL_Window * window)
{
    SDL_bool quit = SDL_FALSE;
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
            checkColor(p, defaultColors);
            if (isVictoryOrLose(window, renderer))
            {
                quit = !quit;
            }

        }
        if (!quit)
        {
            drawRendererGrid(renderer, colors);
            SDL_Delay(5);
            SDL_RenderPresent(renderer);
        }
        
    }

}

int main(){
    SDL_Window   * window = NULL;
    SDL_Renderer * renderer = NULL;

    int germe = getpid();
    initialiser_solution(solution, &germe);

    // Debug
    afficher_solution();

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

    initializeColors(colors);
    initializeSolColors(sol_colors);

    drawRendererGrid(renderer, colors);

    SDL_RenderPresent(renderer);
    refreshWindow(renderer, window);

    if (NULL != renderer){
        SDL_DestroyRenderer(renderer);
    }
    if (NULL != window){
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}