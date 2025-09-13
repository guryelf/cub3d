#ifndef BUTTON_H
#define BUTTON_H

#include "ui_element.h"

typedef enum e_button_action
{
    BUTTON_ACTION_NONE,
    BUTTON_ACTION_PLAY,
    BUTTON_ACTION_SETTINGS
} t_button_action;

typedef struct s_button_params
{
    int x, y;
    int width, height;
    void *mlx;
    const char *label;
    t_button_action action;
} t_button_params;

typedef struct s_button
{
    t_ui_element base;
    char *label; // Owned
    t_button_action action;
} t_button;

t_button *button_new(int x, int y, int width, int height, void *mlx, const char *label, t_button_action action);

#endif