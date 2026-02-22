/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:28:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:34:52 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures(char **textures, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	while (textures[i])
	{
		line = skip_spaces(textures[i]);
		if (line[0] == 'N')
			map->no_path = ft_strdup(skip_spaces(line + 2));
		else if (line[0] == 'S')
			map->so_path = ft_strdup(skip_spaces(line + 2));
		else if (line[0] == 'W')
			map->we_path = ft_strdup(skip_spaces(line + 2));
		else if (line[0] == 'E')
			map->ea_path = ft_strdup(skip_spaces(line + 2));
		i++;
	}
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path)
		return (1);
	return (0);
}
