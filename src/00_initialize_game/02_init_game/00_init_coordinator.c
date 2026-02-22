/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_coordinator.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:55:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 00:57:31 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_connection(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	return (0);
}

int	init_mlx_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		return (1);
	game->img.addr = (int *)mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (1);
	return (0);
}

int	init_game_resources(t_game *game)
{
	if (init_mlx_connection(game) != 0)
		return (print_error(MSG_MLX_INIT), 1);
	if (load_textures(game) != 0)
		return (print_error(MSG_TEXTURE_LOAD), 1);
	if (init_mlx_window(game) != 0)
		return (print_error(MSG_WINDOW_INIT), 1);
	if (init_camera_vectors(game) != 0)
		return (print_error(MSG_DATA_INIT), 1);
	return (0);
}
