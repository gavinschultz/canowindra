#include "physics.h"
#include "list.h"
#include "debug.h"
#include "game.h"
#include "util.h"

static LLIST *entities = NULL;

void register_entity(ENTITY2D *entity)
{
    LLIST *node = NULL;
    node = add_node(&entities, sizeof(entity));
    node->data = entity;
//    trace("Registering node->data %p entity %p", node->data, entity);
}

void move_objects(fixed t, fixed dt)
{
    LLIST *current = entities;
    LLIST *node = NULL;
    ENTITY2D *entity = NULL;

    current = entities;
    while (current != NULL)
    {
        node = current;
        current = current->next;

        entity = (ENTITY2D*)node->data;
        if (entity == NULL)
            continue;

        // Unregister any objects that are no longer valid
        if (entity->invalid)
        {    
            delete_node(&entities, node);
            continue;
        }

        entity->previous = entity->current;

        // Move object - fixed velocity
        entity->current.pos.x += entity->current.vel.x * (fptof(fpdiv(dt, FPONE)));
        entity->current.pos.y += entity->current.vel.y * (fptof(fpdiv(dt, FPONE)));

        // Bounce off edges
        if (sgnf(entity->current.pos.x) * entity->current.pos.x >= app.x_axis)
            entity->current.vel.x = -entity->current.vel.x;
        if (sgnf(entity->current.pos.y) * entity->current.pos.y >= app.y_axis)
            entity->current.vel.y = -entity->current.vel.y;
    }

    entity = (ENTITY2D*)entities->data;
//    trace("Current point x %3.1f y %3.1f", entity->current.pos.x, entity->current.pos.y);
}

void interpolate_objects(fixed alpha)
{
    LLIST *current = entities;
    LLIST *node = NULL;
    ENTITY2D *entity = NULL;
    float alphaf = fptof(alpha);

    while (current != NULL)
    {
        entity = (ENTITY2D*)current->data;
        if (entity == NULL)
            continue;

        entity->render.pos.x = entity->current.pos.x*alphaf + entity->previous.pos.x*(1.0f-alphaf);
        entity->render.pos.y = entity->current.pos.y*alphaf + entity->previous.pos.y*(1.0f-alphaf);
        entity->render.vel.x = entity->current.vel.x*alphaf + entity->previous.vel.x*(1.0f-alphaf);
        entity->render.vel.y = entity->current.vel.y*alphaf + entity->previous.vel.y*(1.0f-alphaf);

        current = current->next;
    }

    entity = (ENTITY2D*)entities->data;
//    trace("Current point x %3.1f y %3.1f", entity->current.pos.x, entity->current.pos.y);
//    trace("Previous point x %3.1f y %3.1f", entity->previous.pos.x, entity->previous.pos.y);
//    trace("Render point x %3.1f y %3.1f", entity->render.pos.x, entity->render.pos.y);
}

void shutdown_physics()
{
    delete_list(&entities);
}
