#include "entities.h"
#include "physics.h"
#include "graphics.h"
#include "util.h"
#include "game.h"
#include "timing.h"
#include "timing_graph.h"
#include "background.h"

static struct Entity2D points[100];

void draw_scene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_grid();
//    draw_background2();
    draw_background();
    draw_points();
    draw_timing_graph();
    SDL_GL_SwapBuffers();
}

void init_entities()
{
    init_points();
    init_background();
}

static void init_points()
{
    int i;

    for (i=0; i<sizeof(points) / sizeof(*points); i++)
    {
        points[i].current.pos.x = randsgn() * randf(app.x_axis);
        points[i].current.pos.y = randsgn() * randf(app.y_axis);
        points[i].current.vel.x = randsgn() * randf(200.0f);
        points[i].current.vel.y = randsgn() * randf(200.0f);
        points[i].invalid = 0;
//        trace("Initialising point %p", &points[i]);
        register_entity(&points[i]);
    }
}

static void draw_points()
{
    int i;

    glPushMatrix();
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (i=0; i<sizeof(points) / sizeof(*points); i++)
    {
        if (points[i].invalid)
            continue;
        glVertex2f(points[i].render.pos.x, points[i].render.pos.y);
    }
    glEnd();
    glPopMatrix();
}

void draw_grid()
{
    const struct GFX_Screen *screen = get_gfx_info();

    // Draw frame
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-screen->axes.x+5.0f, -screen->axes.y+5.0f);
    glVertex2f(-screen->axes.x+5.0f, screen->axes.y-5.0f);
    glVertex2f(screen->axes.x-5.0f, screen->axes.y-5.0f);
    glVertex2f(screen->axes.x-5.0f, -screen->axes.y+5.0f);
    glEnd();
    glPopMatrix();
}
