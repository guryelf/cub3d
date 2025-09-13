#include "stats.h"
#include <sys/time.h>
#include <stdlib.h>

static double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

static void stats_init(t_entity *self, void *params)
{
    t_stats *stats = (t_stats *)self;
    stats->scene = params;
    stats->moves = 0;
    stats->start_time = get_time();
    stats->end_time = 0;
    stats->doors_opened = 0;
}

static void stats_update(t_entity *self)
{
    t_stats *stats = (t_stats *)self;
    if (stats->scene->state == STATE_GAME)
    {
        if (stats->scene->key_w || stats->scene->key_s || stats->scene->key_a || stats->scene->key_d ||
            stats->scene->key_up || stats->scene->key_down || stats->scene->key_left || stats->scene->key_right)
            stats->moves++;
    }
    else if (stats->scene->state == STATE_COMPLETION && stats->end_time == 0)
        stats->end_time = get_time();
}

static void stats_render(t_entity *self)
{
    (void)self;
}

static const t_vtable stats_vtable = {
    stats_init,
    stats_update,
    stats_render
};

t_stats *stats_new(t_scene *scene)
{
    return (t_stats *)entity_new(sizeof(t_stats), &stats_vtable, scene, ENTITY_STATS);
}