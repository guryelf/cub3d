#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include "player.h"
#include "img.h"
#include "ray.h"
#include "map.h"

#define WIDTH 1280
#define HEIGHT 720

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MOVE_SPEED 0.13
#define ROT_SPEED 0.08

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       img;
    t_map       map;
    t_player    player;
    t_ray       ray;
    t_img       textures[4];
}   t_game;

int     init_game_resources(t_game *game);
int     init_mlx(t_game *game);
int     init_data(t_game *game);
int     load_textures(t_game *game);
void    start_game(t_game *game);
int     render_frame(t_game *game);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
int     create_rgb(int r, int g, int b);
void    draw_background(t_game *game, int x, t_ray *ray);
void    draw_textured_wall(t_game *game, int x, t_ray *ray);
int     clean_exit(t_game *game);
int     handle_keypress(int keycode, t_game *game);
void    move_forward(t_game *game);
void    move_backward(t_game *game);
void    move_left(t_game *game);
void    move_right(t_game *game);
void    rotate_left(t_game *game);
void    rotate_right(t_game *game);

#endif
