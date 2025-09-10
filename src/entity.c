#include "entity.h"
#include <stdlib.h>
#include <mlx.h>

t_entity *entity_new(size_t size, const t_vtable *vtable, void *params)
{
    t_entity *entity = malloc(size);
    if (!entity)
        return NULL;
    entity->vtable = vtable;
    entity->heap.count = 0;
    for (int i = 0; i < MAX_HEAP; i++)
        entity->heap.entries[i].ptr = NULL;
    if (vtable && vtable->init)
        vtable->init(entity, params);
    return entity;
}

void entity_delete(t_entity *entity)
{
    if (!entity)
        return;
    for (int i = 0; i < entity->heap.count; i++)
    {
        void *ptr = entity->heap.entries[i].ptr;
        if (!ptr)
            continue;
        if (entity->heap.entries[i].type == HEAP_ENTITY)
            entity_delete((t_entity *)ptr);
        else if (entity->heap.entries[i].type == HEAP_MLX_IMAGE)
            mlx_destroy_image(((t_game *)entity)->mlx, ptr); // Assumes game has mlx
        else if (entity->heap.entries[i].type == HEAP_MLX_WIN)
            mlx_destroy_window(((t_game *)entity)->mlx, ptr);
        else if (entity->heap.entries[i].type == HEAP_RAW)
            free(ptr);
    }
    free(entity);
}

void entity_add_heap(t_entity *entity, void *ptr, t_heap_type type)
{
    if (!entity || !ptr || entity->heap.count >= MAX_HEAP)
        return;
    entity->heap.entries[entity->heap.count].ptr = ptr;
    entity->heap.entries[entity->heap.count].type = type;
    entity->heap.count++;
}