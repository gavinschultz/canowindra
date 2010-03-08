#include <time.h>
#include "SDL.h"
#include "game.h"
#include "debug.h"
#include "graphics.h"
#include "timing.h"

#define Y_AXIS              288.0f      /* extent of y-axis */
#define X_AXIS              512.0f      /* extent of x-axis */

struct GameState app;

// Putting these here because they don't need to be made available anywhere else
void init(void);
void handle_event(SDL_Event *);
void shutdown_app(void);

int main(int argc, char *argv[])
{
    SDL_Event event;
    init();

    while (!app.quit)
    {
        start_frame();

        if (SDL_PollEvent(&event))
        {
            handle_event(&event);
        }

        SDL_GL_SwapBuffers();
        end_frame();
    }

    return 0;
}

void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        trace("SDL initialization failed: %s.", SDL_GetError());
        exit(1);
    }

    atexit(shutdown_app);
    srand((unsigned int)time(NULL));

    // Graphics init
    init_gfx(X_AXIS, Y_AXIS);
}

void shutdown_app()
{
    shutdown_gfx();
}

void handle_event(SDL_Event *event)
{
    SDLKey key = SDLK_CLEAR;

    if (event == NULL)
        return;

    // These events may be used at any time, even when the game is paused
    switch(event->type)
    {
        case SDL_QUIT:
            app.quit = 1;
            break;
        case SDL_KEYDOWN:
            key = event->key.keysym.sym;
            switch(key)
            {
                case SDLK_q:
                case SDLK_ESCAPE:
                    app.quit = 1;
                    break;
                case SDLK_p:
                    app.paused = (app.paused ? 0 : 1);
                    break;
                case SDLK_RETURN:
                    if (event->key.keysym.mod & KMOD_ALT)
                        toggle_fullscreen();
                    break;
                case SDLK_v:
                    toggle_vsync();
                    break;
            }
            break;
        case SDL_VIDEORESIZE:
            resize_window(event->resize.w, event->resize.h);
            break;
    }
}

