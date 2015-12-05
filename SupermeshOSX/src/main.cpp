#include "SMFramework.h"
#include "SMApplication.h"
#include <SDL2/SDL.h>

//------------------------------------------------------------------------
// Entry point.
//------------------------------------------------------------------------
int main() {
    // initalize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // create application and initialize
    g_App = new SMApplication();
    g_App->Initialize();
    
    // run application
    g_App->Run();
    
    // quit SDL
    SDL_Quit();
}