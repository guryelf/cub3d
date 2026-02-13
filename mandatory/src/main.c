/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/08 19:17:26 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	if (init_parsing(argv[1], &game.map) != 0)
		return (1);
	if (init_mlx(&game) != 0)
	{
		write(2, "Error\nMLX initialization failed\n", 33);
		return (1);
	}
	if (load_textures(&game) != 0)
	{
		write(2, "Error\nTexture loading failed\n", 30);
		return (1);
	}
	if (init_data(&game) != 0)
	{
		write(2, "Error\nData initialization failed\n", 34);
		return (1);
	}
	write(1, "Phase 1 Complete: MLX, Textures, Player initialized!\n", 54);
	return (0);
}