/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_game_resources.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:55:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 19:02:23 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_game_resources(t_game *game)
{
	if (init_mlx(game) != 0)
	{
		write(2, "Error\nMLX initialization failed\n", 33);
		return (1);
	}
	if (load_textures(game) != 0)
	{
		write(2, "Error\nTexture loading failed\n", 30);
		return (1);
	}
	if (set_player_position(game) != 0)
	{
		write(2, "Error\nData initialization failed\n", 34);
		return (1);
	}
	return (0);
}
