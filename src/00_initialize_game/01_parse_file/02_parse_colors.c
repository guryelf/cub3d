/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parse_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:29:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:47:37 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extract_rgb(char *line, t_texture *tex)
{
	char	**split;
	int		j;

	split = ft_split(skip_spaces(line + 1), ',');
	if (!split)
		return (1);
	tex->r = ft_atoi(split[0]);
	tex->g = ft_atoi(split[1]);
	tex->b = ft_atoi(split[2]);
	j = 0;
	while (split[j])
		free(split[j++]);
	free(split);
	tex->set = 1;
	return (0);
}

int	parse_colors(char **colors, t_map *map)
{
	int			i;
	char		*line;
	t_texture	*tex;

	i = -1;
	while (colors[++i])
	{
		line = skip_spaces(colors[i]);
		if (line[0] == 'F')
			tex = &map->floor;
		else
			tex = &map->ceil;
		if (extract_rgb(line, tex) != 0)
			return (1);
	}
	return (0);
}
