#include "SMWindow.h"
#include <SDL2/SDL.h>

#define WINDOW static_cast<SDL_Window*>(m_Window)
#define RENDERER static_cast<SDL_Renderer*>(m_Renderer)

SMWindow::SMWindow(const char* title, SMInt32 width, SMInt32 height) {
    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN);
    m_Renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(WINDOW));
}

SMWindow::~SMWindow() {
    SDL_DestroyWindow(WINDOW);
}

void SMWindow::Show() {
    SDL_ShowWindow(WINDOW);
}

void SMWindow::Hide() {
    SDL_HideWindow(WINDOW);
}

void SMWindow::Flip() {
    SDL_RenderPresent(RENDERER);
}

SMBool SMWindow::Poll() {
    SDL_Event e;
    
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return false;
    }
    
    return true;
}