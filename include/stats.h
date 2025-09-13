#ifndef STATS_H
#define STATS_H

#include "entity.h"

// Forward declaration of t_scene to break circular dependency
typedef struct s_scene t_scene;

typedef struct s_stats
{
    t_entity base;
    t_scene *scene;
    int moves;
    double start_time;
    double end_time;
    int doors_opened;
} t_stats;

t_stats *stats_new(t_scene *scene);

#endif