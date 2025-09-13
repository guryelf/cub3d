#include "renderer.h"
#include <stdlib.h>
#include <mlx.h>

void render_ray(t_renderer *renderer, int x, int width, int height);

static void renderer_init(t_entity *self, void *params)
{
    t_renderer *renderer = (t_renderer *)self;
    t_renderer_params *p = (t_renderer_params *)params;
    if (!p || !p->scene)
        return;
    renderer->scene = p->scene;
    renderer->img = mlx_new_image(renderer->scene->mlx, 800, 600);
    if (!renderer->img)
        return;
    renderer->img_data = mlx_get_data_addr(renderer->img, &renderer->bpp, &renderer->size_line, &renderer->endian);
    entity_add_heap(self, renderer->img);
}

static void renderer_update(t_entity *self)
{
    (void)self;
}

static void renderer_render(t_entity *self)
{
    t_renderer *renderer = (t_renderer *)self;
    t_scene *scene = renderer->scene;
    if (scene->state != STATE_GAME)
        return;
    t_map *map = (t_map *)scene->entities[0];
    t_player *player = (t_player *)scene->entities[1];
    int width = 800, height = 600;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            ((int *)renderer->img_data)[y * (renderer->size_line / 4) + x] = 0;

    for (int x = 0; x < width; x++)
        render_ray(renderer, x, width, height);

    mlx_put_image_to_window(scene->mlx, scene->win, renderer->img, 0, 0);
}

static const t_vtable renderer_vtable = {
    renderer_init,
    renderer_update,
    renderer_render
};

t_renderer *renderer_new(t_scene *scene)
{
    t_renderer_params params = {scene};
    return (t_renderer *)entity_new(sizeof(t_renderer), &renderer_vtable, &params, ENTITY_RENDERER);
}