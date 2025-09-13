#include "scene.h"
#include "menu.h"
#include <stdlib.h>

static void menu_init(t_entity *self, void *params)
{
    t_menu *menu = (t_menu *)self;
    menu->child_count = 0;
    void *mlx = params;
    t_button *play = button_new(300, 200, 200, 50, mlx, "Play", BUTTON_ACTION_PLAY);
    t_button *settings = button_new(300, 300, 200, 50, mlx, "Settings", BUTTON_ACTION_SETTINGS);
    menu->children[menu->child_count++] = (t_entity *)play;
    menu->children[menu->child_count++] = (t_entity *)settings;
    entity_add_heap(self, play);
    entity_add_heap(self, settings);
}

static void menu_update(t_entity *self)
{
    t_menu *menu = (t_menu *)self;
    for (int i = 0; i < menu->child_count; i++)
        if (menu->children[i]->vtable->update)
            menu->children[i]->vtable->update(menu->children[i]);
}

static void menu_render(t_entity *self)
{
    t_menu *menu = (t_menu *)self;
    for (int i = 0; i < menu->child_count; i++)
        if (menu->children[i]->vtable->render)
            menu->children[i]->vtable->render(menu->children[i]);
}

static const t_vtable menu_vtable = {
    menu_init,
    menu_update,
    menu_render
};

t_menu *menu_new(void *mlx)
{
    return (t_menu *)entity_new(sizeof(t_menu), &menu_vtable, mlx, ENTITY_UI);
}