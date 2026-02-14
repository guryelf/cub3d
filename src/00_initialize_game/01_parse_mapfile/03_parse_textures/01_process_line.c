/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_process_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 17:40:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	validate_color_range(t_texture *tex)
{
	if (tex->r < 0 || tex->r > 255)
		return (TEX_ERR_COLOR_RANGE);
	if (tex->g < 0 || tex->g > 255)
		return (TEX_ERR_COLOR_RANGE);
	if (tex->b < 0 || tex->b > 255)
		return (TEX_ERR_COLOR_RANGE);
	return (0);
}

static int	parse_rgb_values(char **split, t_texture *tex)
{
	int	i;

	tex->r = ft_atoi(split[0]);
	tex->g = ft_atoi(split[1]);
	tex->b = ft_atoi(split[2]);
	i = 0;
	while (i < 3)
		free(split[i++]);
	free(split);
	if (validate_color_range(tex))
		return (TEX_ERR_COLOR_RANGE);
	tex->set = 1;
	return (0);
}

int	parse_color_values(char *line, t_texture *tex)
{
	char	**split;
	int		i;

	if (tex->set)
		return (TEX_ERR_DUPLICATE);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (TEX_ERR_INVALID_COLOR);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		while (--i >= 0)
			free(split[i]);
		free(split);
		return (TEX_ERR_INVALID_COLOR);
	}
	return (parse_rgb_values(split, tex));
}

int	get_texture_type(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (4);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (5);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (6);
	return (0);
}

int	process_line(char *line, t_map *map)
{
	int	type;

	type = get_texture_type(line);
	if (type == 0)
		return (0);
	if (type == 1)
		return (set_texture_path(&map->no_path, line, 3));
	if (type == 2)
		return (set_texture_path(&map->so_path, line, 3));
	if (type == 3)
		return (set_texture_path(&map->we_path, line, 3));
	if (type == 4)
		return (set_texture_path(&map->ea_path, line, 3));
	if (type == 5)
		return (parse_color_values(line + 2, &map->floor));
	return (parse_color_values(line + 2, &map->ceil));
}
