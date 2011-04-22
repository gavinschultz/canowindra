#ifndef  GRAPHICS_INC
#define  GRAPHICS_INC

#include "SDL_opengl.h"
#include "soil.h"

#define DEFAULT_HRES        1024        /* default horizontal resolution */
#define DEFAULT_VRES        576         /* default vertical resolution */
#define DEFAULT_COLORDEPTH  32          /* default color depth */
#define DEFAULT_FULLSCREEN  0           /* default to full-screen mode? */

struct GFX_Res
{
    GLsizei h, v;
};

struct GFX_Axes
{
    GLfloat x, y;
};

struct GFX_Screen
{
    struct GFX_Axes axes;
    struct GFX_Res res;
    struct GFX_Res best_res;
    int colordepth;
    int fullscreen;
    int vsync;
};

struct GLRGBColor
{
    float r, g, b;
};

struct Vertex
{
    GLfloat position[2];
    GLfloat color[3];
};

struct Sprite
{
    GLuint texture_id;
};

void init_gfx(const GLfloat x_axis, const GLfloat y_axis);
static void init_gl(void);
void shutdown_gfx(void);
void toggle_fullscreen(void);
void toggle_vsync(void);
void resize_window(GLsizei w, GLsizei h);
struct GLRGBColor int_to_glrgb(const uint32_t);
const struct GFX_Screen *get_gfx_info(void);

static void load_sprites(void); // load all non-background textures from disk
static void load_background(void); // load all background textures from disk

#endif
