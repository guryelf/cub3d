#include "text.h"
#include <stdlib.h>
#include <string.h>

static void text_init(t_entity *self, void *params)
{
    t_text *text = (t_text *)self;
    t_text_params *p = (t_text_params *)params;
    ui_element_init(self, params);
    text->content = p && p->content ? strdup(p->content) : NULL;
    if (text->content)
        entity_add_heap(self, text->content);
}

static void text_update(t_entity *self)
{
    (void)self;
}

static void text_render(t_entity *self)
{
    t_text *text = (t_text *)self;
    t_scene *scene = (t_scene *)text->base.mlx;
    if (text->content)
        mlx_string_put(scene->mlx, scene->win, text->base.x, text->base.y, 0xFFFFFF, text->content);
}

static const t_vtable text_vtable = {
    text_init,
    text_update,
    text_render
};

t_text *text_new(int x, int y, void *mlx, const char *content)
{
    t_text_params params = {x, y, NULL, content};
    return (t_text *)entity_new(sizeof(t_text), &text_vtable, &params, ENTITY_UI);
}