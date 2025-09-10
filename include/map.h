#ifndef MAP_H
# define MAP_H

#include "entity.h"

typedef struct s_map
{
    t_entity		base;
    char			**grid;          // 2D array representing the map
    int				width;          // Width of the map
    int				height;         // Height of the map
}						t_map;

extern const t_vtable g_map_vtable;

t_map *map_new(char **grid, int width, int height);
int map_is_wall(t_map *map, int x, int y);
void map_print(t_map *map);

#endif