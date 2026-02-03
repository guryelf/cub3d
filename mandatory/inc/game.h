#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include "player.h"
#include "img.h"
#include "ray.h"
#include "map.h"


typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       img;
    t_map       map;
    t_player    player;
    t_ray       ray;
    t_img       textures[1]; 
}   t_game;


#endif
