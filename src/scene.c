#include "scene.h"
#include "door.h"
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>

static void scene_init(t_entity *self, void *params)
{
    t_scene *scene = (t_scene *)self;
    t_scene_params *p = (t_scene_params *)params;
    if (!p || !p->map_file)
    {
        printf("Scene init: Invalid params\n");
        return;
    }
    scene->entity_count = 0;
    scene->mlx = NULL;
    scene->win = NULL;
    scene->key_w = 0;
    scene->key_s = 0;
    scene->key_a = 0;
    scene->key_d = 0;
    scene->key_up = 0;
    scene->key_down = 0;
    scene->key_left = 0;
    scene->key_right = 0;
    scene->mouse_clicked = 0;
    scene->state = STATE_MENU;
    scene->mlx = mlx_init();
    if (!scene->mlx)
    {
        printf("Scene init: MLX init failed\n");
        return;
    }
    scene->win = mlx_new_window(scene->mlx, 800, 600, "Cub3D");
    if (!scene->win)
    {
        printf("Scene init: Window creation failed\n");
        return;
    }
    t_map *map = map_new(p->map_file, scene->mlx);
    if (!map || !map->is_valid)
    {
        printf("Scene init: Invalid map\n");
        return;
    }
    t_player *player = player_new(map->player_x, map->player_y, map->player_angle);
    if (!player)
    {
        printf("Scene init: Player creation failed\n");
        return;
    }
    player->scene = scene;
    t_renderer *renderer = renderer_new(scene);
    if (!renderer)
    {
        printf("Scene init: Renderer creation failed\n");
        return;
    }
    t_stats *stats = stats_new(scene);
    t_menu *menu = menu_new(scene); // Pass scene as mlx for button clicks
    t_completion *completion = completion_new(scene, stats);
    scene->entities[scene->entity_count++] = (t_entity *)map;
    scene->entities[scene->entity_count++] = (t_entity *)player;
    scene->entities[scene->entity_count++] = (t_entity *)renderer;
    scene->entities[scene->entity_count++] = (t_entity *)menu;
    scene->entities[scene->entity_count++] = (t_entity *)completion;
    scene->entities[scene->entity_count++] = (t_entity *)stats;
    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            if (map->grid[y][x] == 'D')
            {
                t_door *door = door_new(x + 0.5f, y + 0.5f, false);
                door->scene = scene;
                map->grid[y][x] = door->is_open ? '0' : '1';
                scene->entities[scene->entity_count++] = (t_entity *)door;
                entity_add_heap(self, door);
            }
    entity_add_heap(self, map);
    entity_add_heap(self, player);
    entity_add_heap(self, renderer);
    entity_add_heap(self, menu);
    entity_add_heap(self, completion);
    entity_add_heap(self, stats);
    entity_add_heap(self, scene->mlx);
    entity_add_heap(self, scene->win);
}

static void scene_update(t_entity *self)
{
    t_scene *scene = (t_scene *)self;
    if (scene->state == STATE_GAME)
    {
        for (int i = 0; i < scene->entity_count; i++)
            if (scene->entities[i]->type != ENTITY_UI && scene->entities[i]->vtable->update)
                scene->entities[i]->vtable->update(scene->entities[i]);
        // Check for completion (e.g., reach (3, 3))
        t_player *player = (t_player *)scene->entities[1];
        if ((int)player->x == 3 && (int)player->y == 3)
            scene->state = STATE_COMPLETION;
    }
    else if (scene->state == STATE_MENU || scene->state == STATE_SETTINGS)
    {
        for (int i = 0; i < scene->entity_count; i++)
            if (scene->entities[i]->type == ENTITY_UI && scene->entities[i]->vtable->update)
                scene->entities[i]->vtable->update(scene->entities[i]);
    }
    // Always update stats
    for (int i = 0; i < scene->entity_count; i++)
        if (scene->entities[i]->type == ENTITY_STATS && scene->entities[i]->vtable->update)
            scene->entities[i]->vtable->update(scene->entities[i]);
}

static void scene_render(t_entity *self)
{
    t_scene *scene = (t_scene *)self;
    mlx_clear_window(scene->mlx, scene->win);
    if (scene->state == STATE_GAME)
    {
        for (int i = 0; i < scene->entity_count; i++)
            if (scene->entities[i]->type != ENTITY_UI && scene->entities[i]->type != ENTITY_STATS &&
                scene->entities[i]->vtable->render)
                scene->entities[i]->vtable->render(scene->entities[i]);
    }
    else if (scene->state == STATE_MENU)
        ((t_menu *)scene->entities[3])->vtable->render((t_entity *)scene->entities[3]);
    else if (scene->state == STATE_COMPLETION)
        ((t_completion *)scene->entities[4])->vtable->render((t_entity *)scene->entities[4]);
}

static const t_vtable scene_vtable = {
    scene_init,
    scene_update,
    scene_render
};

t_scene *scene_new(const char *map_file)
{
    t_scene_params params = {map_file, NULL};
    t_scene *scene = (t_scene *)entity_new(sizeof(t_scene), &scene_vtable, &params, ENTITY_GAME);
    if (!scene || !scene->entities[0] || !scene->entities[1] || !scene->entities[2] || !scene->mlx || !scene->win)
    {
        printf("Scene new: Creation failed\n");
        entity_delete((t_entity *)scene);
        return NULL;
    }
    return scene;
}