#ifndef ENTITY_H
#define ENTITY_H


#include <stdlib.h>
#include <mlx.h>
#include "mlx.h"
#include "scene.h"

#define MAX_HEAP 16

typedef struct s_entity t_entity;

typedef struct s_vtable
{
    void (*init)(t_entity *self, void *params);
    void (*update)(t_entity *self);
    void (*render)(t_entity *self);
} t_vtable;

typedef enum e_entity_type
{
    ENTITY_BASE, // Player, map, door
    ENTITY_GAME, // Scene (mlx, win)
    ENTITY_RENDERER, // Main renderer
    ENTITY_TEXTURE, // Wall textures
    ENTITY_UI, // Buttons, text
    ENTITY_STATS // Gameplay stats
} t_entity_type;

typedef struct s_heap_list
{
    void *ptrs[MAX_HEAP];
    int count;
} t_heap_list;

typedef struct s_entity
{
    const t_vtable *vtable;
    t_heap_list heap;
    t_entity_type type;
} t_entity;

t_entity *entity_new(size_t size, const t_vtable *vtable, void *params, t_entity_type type);
void entity_delete(t_entity *entity);
void entity_add_heap(t_entity *entity, void *ptr);

#endif