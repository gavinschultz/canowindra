#include "timing_graph.h"
#include "game.h"
#include "graphics.h"
#include "timing.h"

static int timing_graph_enabled = 0;

void toggle_timing_graph()
{
    timing_graph_enabled = !timing_graph_enabled;
}

void draw_timing_graph()
{
    int i, proximity;
    static float graph_times[512];
    static int current_graph_point = 0;
    static fixed current_time = 0;
    static fixed prev_time = 0;

    if (!timing_graph_enabled)
        return;

    current_time = get_time();

    graph_times[current_graph_point] = (float)(current_time - prev_time) / 100.0f;
    if (++current_graph_point >= (sizeof(graph_times)/sizeof(graph_times[0])))
        current_graph_point = 0;

    glPushMatrix();
    glTranslatef(-app.x_axis, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<sizeof(graph_times)/sizeof(graph_times[0]); i++)
    {
        if (graph_times[i] == 0.0f)
            continue;

        proximity = current_graph_point - i;
        if (proximity >= 0 && proximity <= 25)
        {
            glColor3f(0.0f + (0.04f * (proximity)), 0.0f + (0.04f * (proximity)), 1.0f);
        }
        else
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        glVertex2f((i*2.0f), -graph_times[i] * 10.0f);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();

    glBegin(GL_POINTS);

    glEnd();
    glPopMatrix();

    prev_time = current_time;
}
