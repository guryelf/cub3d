#ifndef TEXT_H
#define TEXT_H

#include "ui_element.h"

typedef struct s_text_params
{
    int x, y;
    void *mlx;
    const char *content;
} t_text_params;

typedef struct s_text
{
    t_ui_element base;
    char *content; // Owned
} t_text;

t_text *text_new(int x, int y, void *mlx, const char *content);

#endif