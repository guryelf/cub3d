/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_validate_enclosure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 12:30:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	free_grid_copy(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static int	flood_fill(char **grid, t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (0);
	if (grid[y][x] == ' ')
		return (1);
	grid[y][x] = 'V';
	if (flood_fill(grid, map, x + 1, y)
		|| flood_fill(grid, map, x - 1, y)
		|| flood_fill(grid, map, x, y + 1)
		|| flood_fill(grid, map, x, y - 1))
		return (1);
	return (0);
}

static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = ft_calloc(map->height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	validate_enclosure(t_map *map)
{
	char	**grid_copy;
	int		result;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (1);
	result = flood_fill(grid_copy, map, map->player_x, map->player_y);
	free_grid_copy(grid_copy, map->height);
	return (result);
}
