#include "ui_element.h"
#include <stdlib.h>
#include <mlx.h>

static void ui_element_init(t_entity *self, void *params)
{
    t_ui_element *ui = (t_ui_element *)self;
    t_ui_element_params *p = (t_ui_element_params *)params;
    ui->x = p ? p->x : 0;
    ui->y = p ? p->y : 0;
    ui->width = p ? p->width : 0;
    ui->height = p ? p->height : 0;
    ui->mlx = p ? p->mlx : NULL;
    ui->img = NULL;
    if (ui->mlx && ui->width > 0 && ui->height > 0)
    {
        ui->img = mlx_new_image(ui->mlx, ui->width, ui->height);
        if (ui->img)
        {
            ui->img_data = mlx_get_data_addr(ui->img, &ui->bpp, &ui->size_line, &ui->endian);
            entity_add_heap(self, ui->img);
        }
    }
}

static void ui_element_update(t_entity *self)
{
    (void)self;
}

static void ui_element_render(t_entity *self)
{
    (void)self;
}

static const t_vtable ui_element_vtable = {
    ui_element_init,
    ui_element_update,
    ui_element_render
};

t_ui_element *ui_element_new(int x, int y, int width, int height, void *mlx)
{
    t_ui_element_params params = {x, y, width, height, mlx};
    return (t_ui_element *)entity_new(sizeof(t_ui_element), &ui_element_vtable, &params, ENTITY_UI);
}