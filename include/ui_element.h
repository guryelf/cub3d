#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "entity.h"
#include "scene.h"

typedef struct s_ui_element_params
{
    int x, y;
    int width, height;
    void *mlx;
} t_ui_element_params;

typedef struct s_ui_element
{
    t_entity base;
    int x, y;
    int width, height;
    void *mlx; // Non-owning
    void *img; // Optional button background
    char *img_data;
    int bpp, size_line, endian;
} t_ui_element;

t_ui_element *ui_element_new(int x, int y, int width, int height, void *mlx);

#endif