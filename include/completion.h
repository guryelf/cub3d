#ifndef COMPLETION_H
#define COMPLETION_H

#include "entity.h"
#include "text.h"
#include "stats.h"

#define MAX_COMPLETION_TEXT 4

typedef struct s_completion
{
    t_entity base;
    t_entity *children[MAX_COMPLETION_TEXT];
    int child_count;
    t_stats *stats; // Non-owning
} t_completion;

t_completion *completion_new(void *mlx, t_stats *stats);

#endif