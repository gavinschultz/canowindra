#include "background.h"
#include <windows.h>
#include "GLEE.h"
#include "graphics.h"
#include "game.h"
#include "debug.h"
#include "io.h"

static GLuint textures[16];
static const GLfloat box_points[4][2] = { { 0.0, 0.0 }, { 0.0, 128.0 }, { 128.0, 128.0 }, { 128.0, 0.0 } };
//static const GLfloat box_textures[4][2] = { { 0.0, 0.0 }, { 0.0, 0.5 }, { 0.5, 0.5 }, { 0.5, 0.0 } };
static const GLfloat box_textures[32] = { 
    0.0, 0.5, 0.0, 1.0, 0.5, 1.0, 0.5, 0.5,
    0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 0.5,
    0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0,
    0.5, 0.0, 0.5, 0.5, 1.0, 0.5, 1.0, 0.0
};
static const int box_sprite_count = sizeof(box_textures) / sizeof(*box_textures);

static const GLfloat box_colors[4][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 } };
static GLuint shaderprogram;
static GLuint vertexshader;
static GLuint fragmentshader;
static GLuint vbo[2];

static enum AttribIndexes
{
    ATTRIB_POS = 0,
    ATTRIB_COLOR = 1,
    ATTRIB_TEX = 2
};

void init_shaders()
{
    int is_vertexshader_compiled, is_fragmentshader_compiled, is_linked;
    int maxlength;
    char *vertex_infolog, *fragment_infolog, *shader_program_infolog;
    const GLchar *vertexsource, *fragmentsource;

    glGenBuffers(3, vbo);

    // VBO #1, box points
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_points), box_points, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_POS, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTRIB_POS);

    // VBO #2, box colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_colors), box_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTRIB_COLOR);

    // VBO #3, textures
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_textures), box_textures, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_TEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(ATTRIB_TEX);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    vertexsource = file_open("texture120.vert");
    fragmentsource = file_open("texture120.frag");

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
    glCompileShader(vertexshader);
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &is_vertexshader_compiled);
    if(!is_vertexshader_compiled)
    {
        glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxlength);
        vertex_infolog = (char *)malloc(maxlength);
        glGetShaderInfoLog(vertexshader, maxlength, &maxlength, vertex_infolog);
        trace("Vertex shader infolog: %s", vertex_infolog);
        exit(1);
    }

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
    glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &is_fragmentshader_compiled);
    if (!is_fragmentshader_compiled)
    {
        glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxlength);
        fragment_infolog = (char *)malloc(maxlength);
        glGetShaderInfoLog(fragmentshader, maxlength, &maxlength, fragment_infolog);
        trace("Fragment shader infolog: %s", fragment_infolog);
        exit(1);
    }

    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);
//    glBindAttribLocation(shaderprogram, ATTRIB_POS, "in_Position");
//    glBindAttribLocation(shaderprogram, ATTRIB_COLOR, "in_Color");
    glLinkProgram(shaderprogram);
    glGetProgramiv(shaderprogram, GL_LINK_STATUS, (int *)&is_linked);
    if (!is_linked)
    {
        glGetShaderiv(shaderprogram, GL_INFO_LOG_LENGTH, &maxlength);
        shader_program_infolog = (char *)malloc(maxlength);
        glGetProgramInfoLog(shaderprogram, maxlength, &maxlength, shader_program_infolog);
        trace("Shader program infolog: %s", shader_program_infolog);
        exit(1);
    }

//    iTransform = glGetUniformLocation(shaderprogram, "mvpmatrix");
//    glUniformMatrix4fv(iTransform, 1, GL_FALSE, mvpMatrix);
}

void cleanup_shaders()
{
    glDisableVertexAttribArray(ATTRIB_POS);
    glDisableVertexAttribArray(ATTRIB_COLOR);
    glDisableVertexAttribArray(ATTRIB_TEX);
    glDetachShader(shaderprogram, vertexshader);
    glDetachShader(shaderprogram, fragmentshader);
    glDeleteProgram(shaderprogram);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    glDeleteBuffers(2, vbo);
}

void init_background()
{
    static const char *texture_files[] = { "resources\\simple4.tga" };

    textures[0] = SOIL_load_OGL_texture(texture_files[0], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y);
    if (textures[0] > 0)
    {
        trace("loaded texture %d", textures[0]);
    }
    else
    {
        trace("Failed to load texture!");
        exit(1);
    }

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    init_shaders();

    {
        GLenum errcode = glGetError();
        while (errcode != GL_NO_ERROR)
        {
            trace("OpenGL error loading background: %i", errcode);
            errcode = glGetError();
        }
    }
}

void draw_background()
{
    static int x = 0;
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glPushMatrix();
    glUseProgram(shaderprogram);

    x = (x + 8*sizeof(*box_textures)) % sizeof(box_textures);
    glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)x); // &box_textures[8]); //8 * sizeof(GLfloat));

    glDrawArrays(GL_QUADS, 0, 4);

    glUseProgram(0);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    // calls to glGetError() are extremely slow during rendering!
#ifdef GLDEBUG
    {
        GLenum errcode = glGetError();
        while (errcode != GL_NO_ERROR)
        {
            trace("OpenGL error rendering: %i", errcode);
            errcode = glGetError();
        }
    }
#endif
}
