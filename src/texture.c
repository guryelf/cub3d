#include "texture.h"
#include <stdlib.h>
#include <mlx.h>

static void texture_init(t_entity *self, void *params)
{
    t_texture *texture = (t_texture *)self;
    t_texture_params *p = (t_texture_params *)params;
    if (!p || !p->mlx || !p->path)
        return;
    texture->mlx = p->mlx;
    texture->img = mlx_xpm_file_to_image(p->mlx, (char *)p->path, &texture->width, &texture->height);
    if (!texture->img)
        return;
    texture->img_data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
    entity_add_heap(self, texture->img);
}

static void texture_update(t_entity *self)
{
    (void)self;
}

static void texture_render(t_entity *self)
{
    (void)self;
}

static const t_vtable texture_vtable = {
    texture_init,
    texture_update,
    texture_render
};

t_texture *texture_new(void *mlx, const char *path)
{
    t_texture_params params = {mlx, path};
    return (t_texture *)entity_new(sizeof(t_texture), &texture_vtable, &params, ENTITY_TEXTURE);
}