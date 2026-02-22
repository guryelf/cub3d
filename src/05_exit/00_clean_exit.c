/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_clean_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com.tr>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026-02-14 14:14:54 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	free_texture_paths(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	map->no_path = NULL;
	if (map->so_path)
		free(map->so_path);
	map->so_path = NULL;
	if (map->we_path)
		free(map->we_path);
	map->we_path = NULL;
	if (map->ea_path)
		free(map->ea_path);
	map->ea_path = NULL;
}

void	free_map_data(t_map *map)
{
	int	i;

	free_texture_paths(map);
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	get_next_line(-1);
}

int	clean_exit(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map_data(&game->map);
	return (0);
}
