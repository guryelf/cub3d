#ifndef TEXTURE_H
#define TEXTURE_H

#include "entity.h"

typedef struct s_texture_params
{
    void *mlx;
    const char *path;
} t_texture_params;

typedef struct s_texture
{
    t_entity base;
    void *mlx; // Non-owning
    void *img;
    char *img_data;
    int width, height;
    int bpp, size_line, endian;
} t_texture;

t_texture *texture_new(void *mlx, const char *path);

#endif