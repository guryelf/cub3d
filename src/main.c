/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/14 00:55:09 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	initialize_game(t_game *game, char *map_file)
{
	if (validate_mapfile(map_file) != 0)
	{
		return (1);
	}
	if (parse_mapfile(map_file, &game->map) != 0)
	{
		free_map_data(&game->map);
		return (1);
	}
	if (init_game_resources(game) != 0)
	{
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	if (initialize_game(&game, argv[1]) != 0)
		return (1);
	write(1, "Phase 4: Starting game loop...\n", 32);
	start_game(&game);
	return (0);
}
