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

#include "../../inc/cub3d.h"

static void	fill_with_space(char *line, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		line[i] = ' ';
		i++;
	}
}

static char	*fill_line(const char *old_line, int target_width)
{
	char	*new_line;
	int		cur_len;
	int		i;

	cur_len = ft_strlen(old_line);
	new_line = ft_calloc(target_width + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < cur_len)
	{
		new_line[i] = old_line[i];
		i++;
	}
	if (cur_len != target_width)
		fill_with_space(new_line, cur_len, target_width);
	return (new_line);
}

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

static char	*extend_if_needed(const char *old_line, int target_width)
{
	char	*result;
	int		cur_len;

	cur_len = ft_strlen(old_line);
	if (cur_len == target_width)
		result = ft_strdup(old_line);
	else
		result = fill_line(old_line, target_width);
	return (result);
}

int	normalize_map_grid(t_map *map)
{
	int		i;
	char	*new_line;

	map->width = get_max_width(map);
	i = 0;
	while (i < map->height)
	{
		new_line = extend_if_needed(map->grid[i], map->width);
		if (!new_line)
			return (1);
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
	return (0);
}
