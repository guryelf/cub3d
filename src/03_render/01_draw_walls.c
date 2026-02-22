/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_draw_walls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com.tr>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026-02-14 14:14:54 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_tex_x(t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * TEX_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

static int	get_tex_y(double tex_pos)
{
	return ((int)tex_pos & (TEX_HEIGHT - 1));
}

void	draw_background(t_game *game, int x, t_ray *ray)
{
	int	y;
	int	floor_color;
	int	ceil_color;

	floor_color = create_rgb(game->map.floor.r, game->map.floor.g,
			game->map.floor.b);
	ceil_color = create_rgb(game->map.ceil.r, game->map.ceil.g,
			game->map.ceil.b);
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->img, x, y, ceil_color);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(&game->img, x, y, floor_color);
		y++;
	}
}

void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	int		y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = game->textures[ray->tex_num].addr[TEX_HEIGHT
			* get_tex_y(tex_pos) + get_tex_x(ray)];
		my_mlx_pixel_put(&game->img, x, y, color);
		tex_pos += step;
		y++;
	}
}
