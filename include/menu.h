#ifndef MENU_H
#define MENU_H

#include "entity.h"
#include "button.h"

#define MAX_UI_CHILDREN 8

typedef struct s_menu
{
    t_entity base;
    t_entity *children[MAX_UI_CHILDREN];
    int child_count;
} t_menu;

t_menu *menu_new(void *mlx);

#endif