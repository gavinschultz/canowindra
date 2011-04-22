#include <time.h>
#include "SDL.h"
#include "game.h"
#include "debug.h"
#include "graphics.h"
#include "timing.h"
#include "physics.h"
#include "physfs.h"
#include "entities.h"
#include "background.h"
#include "timing_graph.h"

#define Y_AXIS              288.0f      /* extent of y-axis */
#define X_AXIS              512.0f      /* extent of x-axis */
#define DEFAULT_PHYSICS_RATE 100        /* physics updates per second */

struct GameState app;

// Putting these here because they don't need to be made available anywhere else
void init_game(const char*);
void handle_event(SDL_Event *);
void shutdown_app(void);

int main(int argc, char *argv[])
{
    fixed total_time = 0;
    fixed accumulator = 0;
    fixed delta_time = 0;
    SDL_Event event;
    init_game(argv[0]);

    while (!app.quit)
    {
        start_frame();
        delta_time = get_last_frame_time();

        while (SDL_PollEvent(&event))
        {
            handle_event(&event);
        }

        if (!app.paused)
        {
            accumulator += delta_time;
            while (accumulator >= app.step_time)
            {
                move_objects(total_time, app.step_time);
                total_time += app.step_time;
                accumulator -= app.step_time;
            }

            interpolate_objects(fpdiv(accumulator, app.step_time));

            draw_scene();
        }
        end_frame();
    }

    return 0;
}

void init_game(const char* arg0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        trace("SDL initialization failed: %s.", SDL_GetError());
        exit(1);
    }

    atexit(shutdown_app);
    srand((unsigned int)time(NULL));

    app.x_axis = X_AXIS;
    app.y_axis = Y_AXIS;
    app.step_time = FPONE / DEFAULT_PHYSICS_RATE;

    PHYSFS_init(arg0);
    PHYSFS_addToSearchPath(".//resources", 0);
    init_gfx(app.x_axis, app.y_axis);
    init_entities();
}

void shutdown_app()
{
    shutdown_gfx();
    shutdown_physics();
    PHYSFS_deinit();
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
                    {
                        toggle_fullscreen();
                        init_background();
                    }
                    break;
                case SDLK_v:
                    toggle_vsync();
                    break;
                case SDLK_g:
                    toggle_timing_graph();
                    break;
            }
            break;
        case SDL_VIDEORESIZE:
            resize_window(event->resize.w, event->resize.h);
            break;
    }
}

