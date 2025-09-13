#ifndef RENDERER_H
#define RENDERER_H

#include "entity.h"

// Forward declaration
typedef struct s_scene t_scene;

typedef struct s_renderer_params
{
    t_scene *scene;
} t_renderer_params;

typedef struct s_renderer
{
    t_entity base;
    t_scene *scene;
    void *img;
    char *img_data;
    int bpp, size_line, endian;
} t_renderer;

t_renderer *renderer_new(t_scene *scene);

#endif