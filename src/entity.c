#include "entity.h"
#include <stdlib.h>


t_entity *entity_new(size_t size, const t_vtable *vtable, void *params, t_entity_type type)
{
    t_entity *entity = malloc(size);
    if (!entity)
        return NULL;
    entity->vtable = vtable;
    entity->heap.count = 0;
    entity->type = type;
    for (int i = 0; i < MAX_HEAP; i++)
        entity->heap.ptrs[i] = NULL;
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
        void *ptr = entity->heap.ptrs[i];
        if (!ptr)
            continue;
        if (((t_entity *)ptr)->vtable) // t_entity
            entity_delete((t_entity *)ptr);
        else if (entity->type == ENTITY_GAME && i == entity->heap.count - 2) // scene->mlx
        {
            mlx_destroy_image(ptr);
            free(ptr);
        }
        else if (entity->type == ENTITY_GAME && i == entity->heap.count - 1) // scene->win
            mlx_destroy_window(((t_scene *)entity)->mlx, ptr);
        else if (entity->type == ENTITY_RENDERER && i == 0) // renderer->img
            mlx_destroy_image(((t_renderer *)entity)->scene->mlx, ptr);
        else if (entity->type == ENTITY_UI && i == 0) // ui_element->img
            mlx_destroy_image(((t_ui_element *)entity)->mlx, ptr);
        else if (entity->type == ENTITY_TEXTURE && i == 0) // texture->img
            mlx_destroy_image(((t_texture *)entity)->mlx, ptr);
        else
            free(ptr);
    }
    free(entity);
}

void entity_add_heap(t_entity *entity, void *ptr)
{
    if (!entity || !ptr || entity->heap.count >= MAX_HEAP)
        return;
    entity->heap.ptrs[entity->heap.count++] = ptr;
}