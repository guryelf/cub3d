#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "player.h"
#include "map.h"
#include "renderer.h"
#include "menu.h"
#include "completion.h"

#define MAX_ENTITIES 16

typedef enum e_scene_state
{
    STATE_MENU,
    STATE_GAME,
    STATE_SETTINGS,
    STATE_COMPLETION
} t_scene_state;

typedef struct s_scene_params
{
    const char *map_file;
    void *mlx;
} t_scene_params;

typedef struct s_scene
{
    t_entity base;
    t_entity *entities[MAX_ENTITIES];
    int entity_count;
    void *mlx;
    void *win;
    int key_w, key_s, key_a, key_d;
    int key_up, key_down, key_left, key_right;
    int mouse_clicked;
    t_scene_state state;
} t_scene;

t_scene *scene_new(const char *map_file);

#endif