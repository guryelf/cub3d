/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/13 19:42:36 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	if (init_parsing(argv[1], &game.map) != 0)
	{
		free_map_data(&game.map);
		return (1);
	}
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
	write(1, "Phase 4: Starting game loop...\n", 32);
	start_game(&game);
	return (0);
}