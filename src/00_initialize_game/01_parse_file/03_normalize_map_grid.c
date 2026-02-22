/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_normalize_map_grid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:30:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:27:32 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (i < target_width)
		new_line[i++] = ' ';
	return (new_line);
}

static int	get_max_width(char **grid)
{
	int	i;
	int	cur_len;
	int	max_width;

	max_width = 0;
	i = 0;
	while (grid[i])
	{
		cur_len = ft_strlen(grid[i]);
		if (cur_len > max_width)
			max_width = cur_len;
		i++;
	}
	return (max_width);
}

int	normalize_map_grid(char **grid)
{
	int		i;
	int		max_width;
	char	*new_line;

	if (!grid)
		return (1);
	max_width = get_max_width(grid);
	i = 0;
	while (grid[i])
	{
		if ((int)ft_strlen(grid[i]) < max_width)
		{
			new_line = fill_line(grid[i], max_width);
			if (!new_line)
				return (1);
			free(grid[i]);
			grid[i] = new_line;
		}
		i++;
	}
	return (0);
}
