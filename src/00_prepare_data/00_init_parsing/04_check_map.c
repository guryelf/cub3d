/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/08 19:08:36 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_char(c));
}


static int	validate_characters(t_map *map)
{
	int	x, y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y] && map->grid[y][x])
		{
			if (!is_valid_char(map->grid[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}


static int	find_and_store_player(t_map *map)
{
	int	x, y, count = 0;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y] && map->grid[y][x])
		{
			if (is_player_char(map->grid[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
				map->grid[y][x] = '0'; 
				count++;
			}
			x++;
		}
		y++;
	}
	return (count != 1); 
}


static void	normalize_to_rectangle(t_map *map)
{
	int	i, j, cur_len;
	char	*new_line;


	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len > map->width)
			map->width = cur_len;
		i++;
	}


	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len < map->width)
		{
			new_line = ft_calloc(map->width + 1, sizeof(char));
			if (!new_line)
				return ;
			j = 0;
			while (j < cur_len)
			{
				new_line[j] = map->grid[i][j];
				j++;
			}
			
			while (j < map->width)
			{
				new_line[j] = ' ';
				j++;
			}
			free(map->grid[i]);
			map->grid[i] = new_line;
		}
		i++;
	}
}


static void	replace_spaces_with_walls(t_map *map)
{
	int	x, y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			x++;
		}
		y++;
	}
}


static int	validate_walls(t_map *map)
{
	int	x, y;


	y = 0;
	while (y < map->height)
	{
		if (y == 0 || y == map->height - 1)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->grid[y][x] == '0')
					return (1); 
				x++;
			}
		}
		else
		{
			
			if (map->grid[y][0] == '0' || map->grid[y][map->width - 1] == '0')
				return (1);
		}
		y++;
	}
	return (0);
}


static int	flood_fill(char **grid, int x, int y, int width, int height)
{
	
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (1);
	

	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (0);
	

	grid[y][x] = 'V';
	

	if (flood_fill(grid, x + 1, y, width, height) ||
		flood_fill(grid, x - 1, y, width, height) ||
		flood_fill(grid, x, y + 1, width, height) ||
		flood_fill(grid, x, y - 1, width, height))
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

static int	validate_enclosure(t_map *map)
{
	char	**grid_copy;
	int		result;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (1);
	

	result = flood_fill(grid_copy, map->player_x, map->player_y, 
						map->width, map->height);
	
	free_grid_copy(grid_copy, map->height);
	return (result);
}

int	check_map(t_map *map)
{
	if (!map || !map->grid || map->height <= 0)
		return (1);
		

	if (validate_characters(map) != 0)
		return (1);
		

	if (find_and_store_player(map) != 0)
		return (1);
		

	normalize_to_rectangle(map);
	

	replace_spaces_with_walls(map);
	

	if (validate_walls(map) != 0)
		return (1);
	

	if (validate_enclosure(map) != 0)
		return (1);
	
	return (0);
}