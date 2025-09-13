#include "game_loop.h"
#include <mlx.h>
#include <stdio.h>

static int render_frame(void *param);
static int handle_key_press(int key, void *param);
static int handle_key_release(int key, void *param);
static int handle_mouse_press(int button, int x, int y, void *param);
static int handle_mouse_release(int button, int x, int y, void *param);

void game_run(t_scene *scene)
{
    if (!scene)
        return;
    printf("Starting game loop\n");
    mlx_hook(scene->win, 2, 1L<<0, handle_key_press, scene);
    mlx_hook(scene->win, 3, 1L<<1, handle_key_release, scene);
    mlx_mouse_hook(scene->win, handle_mouse_press, scene);
    mlx_hook(scene->win, 5, 1L<<3, handle_mouse_release, scene);
    mlx_loop_hook(scene->mlx, render_frame, scene);
    mlx_hook(scene->win, 17, 0, (int (*)(void *))entity_delete, &scene->base);
    mlx_loop(scene->mlx);
}

static int render_frame(void *param)
{
    t_scene *scene = (t_scene *)param;
    scene->base.vtable->update((t_entity *)scene);
    scene->base.vtable->render((t_entity *)scene);
    return 0;
}

static int handle_key_press(int key, void *param)
{
    t_scene *scene = (t_scene *)param;
    printf("Key pressed: %d\n", key);
    if (key == 65307) // ESC
        entity_delete((t_entity *)scene);
    else if (key == 119) // 'w'
        scene->key_w = 1;
    else if (key == 115) // 's'
        scene->key_s = 1;
    else if (key == 97) // 'a'
        scene->key_a = 1;
    else if (key == 100) // 'd'
        scene->key_d = 1;
    else if (key == 65362) // Up
        scene->key_up = 1;
    else if (key == 65364) // Down
        scene->key_down = 1;
    else if (key == 65361) // Left
        scene->key_left = 1;
    else if (key == 65363) // Right
        scene->key_right = 1;
    return 0;
}

static int handle_key_release(int key, void *param)
{
    t_scene *scene = (t_scene *)param;
    printf("Key released: %d\n", key);
    if (key == 119) // 'w'
        scene->key_w = 0;
    else if (key == 115) // 's'
        scene->key_s = 0;
    else if (key == 97) // 'a'
        scene->key_a = 0;
    else if (key == 100) // 'd'
        scene->key_d = 0;
    else if (key == 65362) // Up
        scene->key_up = 0;
    else if (key == 65364) // Down
        scene->key_down = 0;
    else if (key == 65361) // Left
        scene->key_left = 0;
    else if (key == 65363) // Right
        scene->key_right = 0;
    return 0;
}

static int handle_mouse_press(int button, int x, int y, void *param)
{
    t_scene *scene = (t_scene *)param;
    if (button == 1) // Left click
        scene->mouse_clicked = 1;
    return 0;
}

static int handle_mouse_release(int button, int x, int y, void *param)
{
    t_scene *scene = (t_scene *)param;
    if (button == 1) // Left click
        scene->mouse_clicked = 0;
    return 0;
}