#ifndef MAP_H
#define MAP_H

#include "entity.h"
#include "texture.h"
#include <stdbool.h>

typedef struct s_map_params
{
    const char *map_file;
    void *mlx;
} t_map_params;

typedef struct s_map
{
    t_entity base;
    char **grid;
    int width;
    int height;
    t_texture *no_texture;
    t_texture *so_texture;
    t_texture *we_texture;
    t_texture *ea_texture;
    int floor_color;
    int ceiling_color;
    float player_x;
    float player_y;
    float player_angle;
    bool is_valid;
} t_map;

t_map *map_new(const char *map_file, void *mlx);

#endif