#include "player.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static void player_init(t_entity *self, void *params)
{
    t_player *player = (t_player *)self;
    t_player_params *p = (t_player_params *)params;
    player->scene = NULL;
    if (p)
    {
        player->x = p->x;
        player->y = p->y;
        player->angle = p->angle;
    }
}

static void player_update(t_entity *self)
{
    t_player *player = (t_player *)self;
    if (!player->scene || !player->scene->entities[0])
    {
        printf("Player: No scene or map\n");
        return;
    }
    t_map *map = (t_map *)player->scene->entities[0];
    float speed = 0.1f;
    float dx = 0, dy = 0;
    if (player->scene->key_w || player->scene->key_up)
    {
        dx = cos(player->angle * M_PI / 180) * speed;
        dy = sin(player->angle * M_PI / 180) * speed;
    }
    else if (player->scene->key_s || player->scene->key_down)
    {
        dx = -cos(player->angle * M_PI / 180) * speed;
        dy = -sin(player->angle * M_PI / 180) * speed;
    }
    if (player->scene->key_a || player->scene->key_left)
        player->angle -= 5.0f;
    else if (player->scene->key_d || player->scene->key_right)
        player->angle += 5.0f;
    if (dx != 0 || dy != 0)
    {
        float new_x = player->x + dx;
        float new_y = player->y + dy;
        int map_x = (int)new_x;
        int map_y = (int)new_y;
        if (map_x >= 0 && map_x < map->width &&
            map_y >= 0 && map_y < map->height &&
            map->grid[map_y][map_x] == '0')
        {
            player->x = new_x;
            player->y = new_y;
            printf("Player moved to: (%f, %f), angle: %f\n", player->x, player->y, player->angle);
        }
    }
}

static void player_render(t_entity *self)
{
    (void)self;
}

static const t_vtable player_vtable = {
    player_init,
    player_update,
    player_render
};

t_player *player_new(float x, float y, float angle)
{
    t_player_params params = {x, y, angle};
    return (t_player *)entity_new(sizeof(t_player), &player_vtable, &params, ENTITY_BASE);
}