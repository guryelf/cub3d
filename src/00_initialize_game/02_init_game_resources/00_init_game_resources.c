/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_game_resources.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:55:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 00:57:31 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	init_mlx_connection(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	return (0);
}

static int	init_mlx_window(t_game *game)
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
	{
		write(2, "Error\nMLX initialization failed\n", 33);
		return (1);
	}
	if (load_textures(game) != 0)
	{
		write(2, "Error\nTexture loading failed\n", 30);
		return (1);
	}
	if (init_mlx_window(game) != 0)
	{
		write(2, "Error\nMLX window initialization failed\n", 40);
		return (1);
	}
	if (set_player_position(game) != 0)
	{
		write(2, "Error\nData initialization failed\n", 34);
		return (1);
	}
	return (0);
}
