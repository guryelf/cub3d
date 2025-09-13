#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

// Forward declaration
typedef struct s_scene t_scene;

typedef struct s_player_params
{
    float x, y;
    float angle;
} t_player_params;

typedef struct s_player
{
    t_entity base;
    float x, y;
    float angle;
    t_scene *scene; // Non-owning
} t_player;

t_player *player_new(t_scene *scene, t_player_params *params);

#endif