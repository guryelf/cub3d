#include "door.h"
#include <stdlib.h>
#include <math.h>

static void door_init(t_entity *self, void *params)
{
    t_door *door = (t_door *)self;
    t_door_params *p = (t_door_params *)params;
    door->scene = NULL;
    door->x = p ? p->x : 0;
    door->y = p ? p->y : 0;
    door->is_open = p ? p->is_open : false;
}

static void door_update(t_entity *self)
{
    t_door *door = (t_door *)self;
    t_player *player = (t_player *)door->scene->entities[1];
    t_map *map = (t_map *)door->scene->entities[0];
    t_stats *stats = (t_stats *)door->scene->entities[5];
    float dx = player->x - door->x;
    float dy = player->y - door->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist < 1.0f && (door->scene->key_w || door->scene->key_up))
    {
        bool was_open = door->is_open;
        door->is_open = !door->is_open;
        if (!was_open && door->is_open)
            stats->doors_opened++;
        map->grid[(int)door->y][(int)door->x] = door->is_open ? '0' : '1';
    }
}

static void door_render(t_entity *self)
{
    (void)self;
}

static const t_vtable door_vtable = {
    door_init,
    door_update,
    door_render
};

t_door *door_new(float x, float y, bool is_open)
{
    t_door_params params = {x, y, is_open};
    return (t_door *)entity_new(sizeof(t_door), &door_vtable, &params, ENTITY_BASE);
}