#include "renderer.h"
#include <math.h>

void render_ray(t_renderer *renderer, int x, int width, int height)
{
    t_scene *scene = renderer->scene;
    t_player *player = (t_player *)scene->entities[1];
    t_map *map = (t_map *)scene->entities[0];
    float fov = 60.0f;
    float ray_angle = player->angle - fov / 2 + (float)x / width * fov;
    float ray_rad = ray_angle * M_PI / 180;
    float ray_dx = cos(ray_rad);
    float ray_dy = sin(ray_rad);
    float dist = 0;
    float px = player->x, py = player->y;
    while (dist < 20)
    {
        px += ray_dx * 0.1f;
        py += ray_dy * 0.1f;
        int map_x = (int)px, map_y = (int)py;
        if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
            break;
        if (map->grid[map_y][map_x] == '1')
        {
            dist *= cos((ray_angle - player->angle) * M_PI / 180);
            int wall_height = (int)(height / (dist + 0.1f));
            int wall_top = height / 2 - wall_height / 2;
            int wall_bottom = height / 2 + wall_height / 2;
            if (wall_top < 0) wall_top = 0;
            if (wall_bottom > height) wall_bottom = height;
            t_texture *tex = (ray_dx > 0) ? map->ea_texture : (ray_dx < 0) ? map->we_texture :
                            (ray_dy > 0) ? map->no_texture : map->so_texture;
            int color = (ray_dx > 0) ? 0xFF0000 : (ray_dx < 0) ? 0x00FF00 :
                        (ray_dy > 0) ? 0x0000FF : 0xFFFF00;
            for (int y = 0; y < height; y++)
            {
                int pixel = y * (renderer->size_line / 4) + x;
                if (y < wall_top)
                    ((int *)renderer->img_data)[pixel] = map->ceiling_color != -1 ? map->ceiling_color : 0x333333;
                else if (y < wall_bottom)
                    ((int *)renderer->img_data)[pixel] = tex->img ? 0xFFFFFF : color;
                else
                    ((int *)renderer->img_data)[pixel] = map->floor_color != -1 ? map->floor_color : 0x666666;
            }
            break;
        }
        dist += 0.1f;
    }
}