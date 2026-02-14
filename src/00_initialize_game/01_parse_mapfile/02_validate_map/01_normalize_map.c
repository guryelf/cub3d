/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_normalize_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 12:00:00 by rakman           ###   ########.fr       */
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

static char	*extend_and_fill_line(char *old_line, int target_width)
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
		if (old_line[j] == ' ')
			new_line[j] = '1';
		else
			new_line[j] = old_line[j];
		j++;
	}
	while (j < target_width)
	{
		new_line[j] = '1';
		j++;
	}
	return (new_line);
}

void	normalize_map_grid(t_map *map)
{
	int		i;
	char	*new_line;

	map->width = get_max_width(map);
	i = 0;
	while (i < map->height)
	{
		new_line = extend_and_fill_line(map->grid[i], map->width);
		if (!new_line)
			return ;
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
}
