
#ifndef  PHYSICS_INC
#define  PHYSICS_INC

#include "fixed.h"
#include "geometry2d.h"

typedef struct Entity2D
{
    STATE2D current;
    STATE2D previous;
    STATE2D render;
    int invalid;            // indicates that the entity is no longer valid and can be unregistered from any systems that use it
} ENTITY2D;

void register_entity(ENTITY2D *);
void move_objects(fixed t, fixed dt);
void interpolate_objects(fixed alpha);
void shutdown_physics(void);

#endif
