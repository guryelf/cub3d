#include "completion.h"
#include <stdlib.h>
#include <stdio.h>

static void completion_init(t_entity *self, void *params)
{
    t_completion *completion = (t_completion *)self;
    completion->child_count = 0;
    completion->stats = params;
    void *mlx = completion->stats->scene->mlx;
    char time_str[32];
    sprintf(time_str, "Time: %.2f s", completion->stats->end_time - completion->stats->start_time);
    char moves_str[32];
    sprintf(moves_str, "Moves: %d", completion->stats->moves);
    char doors_str[32];
    sprintf(doors_str, "Doors Opened: %d", completion->stats->doors_opened);
    t_text *title = text_new(300, 150, mlx, "Level Complete!");
    t_text *time = text_new(300, 250, mlx, time_str);
    t_text *moves = text_new(300, 300, mlx, moves_str);
    t_text *doors = text_new(300, 350, mlx, doors_str);
    completion->children[completion->child_count++] = (t_entity *)title;
    completion->children[completion->child_count++] = (t_entity *)time;
    completion->children[completion->child_count++] = (t_entity *)moves;
    completion->children[completion->child_count++] = (t_entity *)doors;
    entity_add_heap(self, title);
    entity_add_heap(self, time);
    entity_add_heap(self, moves);
    entity_add_heap(self, doors);
}

static void completion_update(t_entity *self)
{
    t_completion *completion = (t_completion *)self;
    for (int i = 0; i < completion->child_count; i++)
        if (completion->children[i]->vtable->update)
            completion->children[i]->vtable->update(completion->children[i]);
}

static void completion_render(t_entity *self)
{
    t_completion *completion = (t_completion *)self;
    for (int i = 0; i < completion->child_count; i++)
        if (completion->children[i]->vtable->render)
            completion->children[i]->vtable->render(completion->children[i]);
}

static const t_vtable completion_vtable = {
    completion_init,
    completion_update,
    completion_render
};

t_completion *completion_new(void *mlx, t_stats *stats)
{
    return (t_completion *)entity_new(sizeof(t_completion), &completion_vtable, stats, ENTITY_UI);
}