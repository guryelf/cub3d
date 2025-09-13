#include "include/button.h"
#include <stdlib.h>
#include <mlx.h>
#include <string.h>

static void button_init(t_entity *self, void *params)
{
    t_button *button = (t_button *)self;
    t_button_params *p = (t_button_params *)params;
    ui_element_init(self, params);
    button->label = p && p->label ? strdup(p->label) : NULL;
    if (button->label)
        entity_add_heap(self, button->label);
    button->action = p ? p->action : BUTTON_ACTION_NONE;
    if (button->base.img_data)
        for (int y = 0; y < button->base.height; y++)
            for (int x = 0; x < button->base.width; x++)
                ((int *)button->base.img_data)[y * (button->base.size_line / 4) + x] = 0xAAAAAA; // Gray
}

static void button_update(t_entity *self)
{
    t_button *button = (t_button *)self;
    t_scene *scene = (t_scene *)button->base.mlx; // mlx stores scene pointer
    int mx, my;
    mlx_mouse_get_pos(scene->mlx, scene->win, &mx, &my);
    if (mx >= button->base.x && mx < button->base.x + button->base.width &&
        my >= button->base.y && my < button->base.y + button->base.height &&
        scene->mouse_clicked)
    {
        if (button->action == BUTTON_ACTION_PLAY)
            scene->state = STATE_GAME;
        else if (button->action == BUTTON_ACTION_SETTINGS)
            scene->state = STATE_SETTINGS;
    }
}

static void button_render(t_entity *self)
{
    t_button *button = (t_button *)self;
    t_scene *scene = (t_scene *)button->base.mlx;
    if (button->base.img)
        mlx_put_image_to_window(scene->mlx, scene->win, button->base.img, button->base.x, button->base.y);
    if (button->label)
        mlx_string_put(scene->mlx, scene->win, button->base.x + 10, button->base.y + button->base.height / 2, 0xFFFFFF, button->label);
}

static const t_vtable button_vtable = {
    button_init,
    button_update,
    button_render
};

t_button *button_new(int x, int y, int width, int height, void *mlx, const char *label, t_button_action action)
{
    t_button_params params = {x, y, width, height, mlx, label, action};
    return (t_button *)entity_new(sizeof(t_button), &button_vtable, &params, ENTITY_UI);
}