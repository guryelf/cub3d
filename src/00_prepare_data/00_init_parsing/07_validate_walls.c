/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_validate_walls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:35:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 22:07:43 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	get_max_width(t_map *map)
{
	int	i;
	int	cur_len;
	int	max_width;

	max_width = 0;
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len > max_width)
			max_width = cur_len;
		i++;
	}
	return (max_width);
}

static char	*extend_line(char *old_line, int target_width)
{
	char	*new_line;
	int		j;
	int		cur_len;

	cur_len = ft_strlen(old_line);
	new_line = ft_calloc(target_width + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	j = 0;
	while (j < cur_len)
	{
		new_line[j] = old_line[j];
		j++;
	}
	while (j < target_width)
	{
		new_line[j] = ' ';
		j++;
	}
	return (new_line);
}

void	normalize_to_rectangle(t_map *map)
{
	int		i;
	int		cur_len;
	char	*new_line;

	map->width = get_max_width(map);
	i = 0;
	while (i < map->height)
	{
		cur_len = ft_strlen(map->grid[i]);
		if (cur_len < map->width)
		{
			new_line = extend_line(map->grid[i], map->width);
			if (!new_line)
				return ;
			free(map->grid[i]);
			map->grid[i] = new_line;
		}
		i++;
	}
}

void	replace_spaces_with_walls(t_map *map)
{
	int	x;
	int	y;

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

int	validate_walls(t_map *map)
{
	int	x;
	int	y;

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
			if (map->grid[y][0] == '0'
				|| map->grid[y][map->width - 1] == '0')
				return (1);
		}
		y++;
	}
	return (0);
}
