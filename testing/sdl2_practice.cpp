#include <SDL2/SDL.h>
/*
int main()
{

 SDL_Window* window;
 SDL_Renderer* renderer;
 SDL_Surface* surface;
 SDL_Texture* texture;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
 window = SDL_CreateWindow("Testing",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,400, 400, SDL_WINDOW_SHOWN);
 renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_SOFTWARE);
 surface = SDL_LoadBMP("bird.bmp");
 texture = SDL_CreateTextureFromSurface(renderer,surface);


 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
 SDL_RenderClear(renderer);
 //SDL_RenderCopy(renderer,texture, NULL,NULL);
 //SDL_RenderPresent(renderer);
 SDL_Delay(3000);
 SDL_DestroyWindow(window);
 SDL_Quit();

return 0;


}
*/
int main(void)
{
    SDL_Window      *win = NULL;
    SDL_Renderer    *ren = NULL;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(640, 640, 0, &win, &ren);

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
    bool quit = false;

   surface = SDL_LoadBMP("bird.bmp");
   texture = SDL_CreateTextureFromSurface(ren,surface);

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ) // poll for event
                {
                    //User requests quit
                    if( e.type == SDL_QUIT ) // unless player manually quits
                    {
                        quit = true;
                    }
                }

                 SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                 SDL_RenderClear(ren);
                 SDL_RenderCopy(ren,texture, NULL,NULL);
                 SDL_RenderPresent(ren);
            }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return (0);
}