#ifndef  GEOMETRY2D_INC
#define  GEOMETRY2D_INC

#include    <stdlib.h>
#include    "SDL.h"
#include    "debug.h"

#define PI          3.1415f     /* Simple definition of PI */
#define FULL_DEG    360.0f      /* Number of degrees in a circle */    

typedef struct Point2D
{
    float x, y;
} FPOINT;

typedef struct Rect
{
    float x, y, w, h;
} FRECT;

// For now, no practical difference between a Point2D and a Vector2D
typedef struct Vector2D
{
    float x, y;
} VECTOR2D;

typedef struct State2D
{
    VECTOR2D pos; // position vector
    VECTOR2D vel; // velocity vector
} STATE2D;

// Defines a point, line or N-sided geometric primitive, as well as its position & movement in the game space
typedef struct Primitive
{
    uint32_t start_ticks;   // number of ticks at which this primitive was created
    int32_t lifetime;       // lifetime in milliseconds before the primitive naturally expires e.g. for debris; -1 = infinite
    FPOINT *points;         // Array of points comprising the primitive
    int size;               // Number of points in the primitive (i.e. size of points array)
    FPOINT centroid;        // Central point of the primitive; used as the axis around which rotation occurs
    VECTOR2D velocity;      // The velocity of the primitive
    float angle;            // The angle at which the primitive is rotated; generally only relevant for polygons of 3 sides or more
    float rotation;         // The rate of rotation
    float speed;            // The speed of the primitive. Can be derived from the angle, xVel and yVel, but often handy to store.
    float area;             // Surface area of the primitive. Not usually calculated or used.
    int invisible;          // 1 = do not draw
    FRECT bounding_box;     // Bounding box around the primitive, used for first pass of collision detection
} PRIMITIVE;

// A group of primitives. This structure is convenient as a logical grouping but also allows
// memory for the primitives to be initialised and freed all at once.
// Also a linked list to other primitive systems, allowing for further grouping of entire systems
typedef struct PrimitiveSystem
{
    PRIMITIVE *primitives;          // Array of primitives within this primitive system
    int size;                       // Size of primitives array
    enum PolygonMode mode;          // Point, line or polygon modes
    struct PrimitiveSystem *next;   // link to next primitive system
    struct PrimitiveSystem *prev;   // link to previous primitive system.
} PRIMITIVESYSTEM;

//// Used mainly for spark production, defines an origin either from centroid or from anywhere within an objects area
//enum RelativePrimitivePosition
//{
//    FROM_CENTER,
//    FROM_AREA
//};

//void set_axes(float x, float y);
//void set_time_mult(float t);

// Primitive system movement / management
PRIMITIVESYSTEM *create_primitive_system(int primitive_count, int primitive_size);
void add_primitive_system(PRIMITIVESYSTEM **list, PRIMITIVESYSTEM *ps);
void delete_primitive_system(PRIMITIVESYSTEM **list, PRIMITIVESYSTEM *to_delete);
void move_primitive_systems(PRIMITIVESYSTEM **list);
void clear_primitive_systems(PRIMITIVESYSTEM **list);
PRIMITIVE *create_primitives(int num_of_primitives, int primitive_size);
void set_primitive_position(PRIMITIVE *, float x, float y);
void set_primitive_angle(PRIMITIVE *, float angle);
void move_primitive(PRIMITIVE *);

// For moving objects in 2D space
void move_polygon(FPOINT *points, int size, FPOINT *centroid, VECTOR2D velocity, float *angle, float rotation, FRECT *bounding_box);
void move_line(FPOINT *point1, FPOINT *point2, FPOINT *centroid, VECTOR2D velocity, float rotation);
void move_point(FPOINT *point, VECTOR2D velocity);

// General geometric formulas
float to_radians(float);
float to_degrees(float);
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
void point2_rotate(FPOINT *, const float, const float, const float);
char boxes_colliding(FRECT *, FRECT *);
char box_contains_point(FRECT *, float, float);
char polygon_contains_point(FPOINT *polygon, int sz, float px, float py);
char primitives_colliding(PRIMITIVE *, PRIMITIVE *);
char primitive_contains_point(PRIMITIVE *, FPOINT *);
float get_polygon_area(FPOINT *polygon, int sz);

#endif
