#include    "SDL.h"
#include    <windows.h>
#include    "GLEE.h"
#include    "graphics.h"
#include    "debug.h"
#include    "io.h"

static SDL_Surface *sdlscreen = NULL;
static struct GFX_Screen screen;

void init_gfx(const GLfloat x_axis, const GLfloat y_axis)
{
    static int first_init = 1;
    const SDL_VideoInfo *video_info;
    uint32_t video_flags = 0;

    screen.axes.x = x_axis;
    screen.axes.y = y_axis;

    video_info = SDL_GetVideoInfo();
    if (video_info == NULL)
    {
        trace("Could not obtain SDL video info.");
        exit(1);
    }

    if (video_info->hw_available)
    {
        video_flags |= SDL_HWSURFACE;
    }
    else
    {
        video_flags |= SDL_SWSURFACE;
    }

    if (first_init)
    {
        screen.best_res.h = video_info->current_w;
        screen.best_res.v = video_info->current_h;
        screen.res.h = DEFAULT_HRES;
        screen.res.v = DEFAULT_VRES;
        screen.fullscreen = DEFAULT_FULLSCREEN;
        screen.colordepth = DEFAULT_COLORDEPTH;
        screen.vsync = 1;
        first_init = 0;
    }

    if (screen.fullscreen)
    {
        SDL_ShowCursor(SDL_DISABLE);
        video_flags |= SDL_FULLSCREEN;
        screen.res = screen.best_res;
    }
    else
    {
        SDL_ShowCursor(SDL_ENABLE);
        screen.res.h = DEFAULT_HRES;
        screen.res.v = DEFAULT_VRES;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    sdlscreen = SDL_SetVideoMode(screen.res.h, screen.res.v, screen.colordepth, video_flags | SDL_OPENGL | SDL_ANYFORMAT | SDL_RESIZABLE);
    if (sdlscreen == NULL)
    {
        trace("SDL video mode setting failure: %s", SDL_GetError());
        exit(1);
    }

    init_gl();
    load_sprites();
    load_background();
}

static void init_gl()
{
    GLenum response;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    resize_window(screen.res.h, screen.res.v);

    response = glGetError();
    if (response != GL_NO_ERROR)
    {
        trace("OpenGL error detected: %d", glGetError());
        exit(1);
    }

    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glColor3f(1.0f, 1.0f, 1.0f);
}

void resize_window(GLsizei w, GLsizei h)
{
    GLfloat aspect_ratio;
    GLfloat ortho_ratio;
    GLfloat right, left, top, bottom;
    GLfloat x_scale, y_scale;

    h = (h ? h : 1);
    w = (w ? w : 1);

    // Set viewport to specified dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate and compare viewport dimensions vs. required grid dimensions
    aspect_ratio = (GLfloat)w / (GLfloat)h;
    ortho_ratio = screen.axes.x / screen.axes.y;

    if (aspect_ratio <= ortho_ratio)
    {
        y_scale = (ortho_ratio / aspect_ratio);
        x_scale = 1.0f;
    }
    else
    {
        y_scale = 1.0f;
        x_scale = (aspect_ratio / ortho_ratio);
    }
    left   = -screen.axes.x * x_scale;  right = screen.axes.x * x_scale;
    bottom = -screen.axes.y * y_scale;  top   = screen.axes.y * y_scale;

    gluOrtho2D(left, right, bottom, top);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void toggle_fullscreen()
{
    screen.fullscreen = !screen.fullscreen;
    init_gfx(screen.axes.x, screen.axes.y);
}

void toggle_vsync()
{
    screen.vsync = !screen.vsync;
    if (GLEE_WGL_EXT_swap_control)
        wglSwapIntervalEXT(screen.vsync);
}

const struct GFX_Screen *get_gfx_info()
{
    return &screen;
}

struct GLRGBColor int_to_glrgb(const uint32_t color)
{
    struct GLRGBColor rgb_color;
    rgb_color.r = ((color & 0xFF0000) >> 16) / 255.0f;
    rgb_color.g = ((color & 0xFF00) >> 8) / 255.0f;
    rgb_color.b = (color & 0xFF) / 255.0f;
    return rgb_color;
}

void shutdown_gfx()
{
    SDL_FreeSurface(sdlscreen);
    sdlscreen = NULL;
}

// Load all sprites from disk
static void load_sprites() 
{
    char *buffer = NULL;
    buffer = file_open("simple4.tga");
}

static void load_background()
{

}


