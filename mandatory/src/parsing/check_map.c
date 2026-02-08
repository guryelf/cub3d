/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/08 18:52:17 by rakman           ###   ########.fr       */
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

// Step 1: Basic character validation
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

// Step 2: Player detection and count validation
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
				map->grid[y][x] = '0'; // Replace with empty space
				count++;
			}
			x++;
		}
		y++;
	}
	return (count != 1); // Should have exactly 1 player
}

// Step 3: Normalize irregular map to rectangular
static void	normalize_to_rectangle(t_map *map)
{
	int	i, j, cur_len;
	char	*new_line;

	// Find maximum width
	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len > map->width)
			map->width = cur_len;
		i++;
	}

	// Extend all lines to max width
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
			// Fill remaining with spaces (will be converted to walls)
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

// Step 4: Convert spaces to walls
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

// Step 5: Basic wall validation (edges should be walls)
static int	validate_walls(t_map *map)
{
	int	x, y;

	// Check top and bottom edges
	y = 0;
	while (y < map->height)
	{
		if (y == 0 || y == map->height - 1)
		{
			x = 0;
			while (x < map->width)
			{
				if (map->grid[y][x] == '0')
					return (1); // Empty space on edge
				x++;
			}
		}
		else
		{
			// Check left and right edges
			if (map->grid[y][0] == '0' || map->grid[y][map->width - 1] == '0')
				return (1);
		}
		y++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	if (!map || !map->grid || map->height <= 0)
		return (1);
		
	// Step 1: Validate characters
	if (validate_characters(map) != 0)
		return (1);
		
	// Step 2: Find and store player
	if (find_and_store_player(map) != 0)
		return (1);
		
	// Step 3: Normalize irregular map to rectangle
	normalize_to_rectangle(map);
	
	// Step 4: Replace spaces with walls
	replace_spaces_with_walls(map);
	
	// Step 5: Validate walls
	if (validate_walls(map) != 0)
		return (1);
	
	return (0);
}