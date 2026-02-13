/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 05:15:30 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"

static int	parse_color_values(char *line, t_texture *tex)
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
	tex->r = ft_atoi(split[0]);
	tex->g = ft_atoi(split[1]);
	tex->b = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	if (tex->r < 0 || tex->r > 255 || tex->g < 0 || tex->g > 255
		|| tex->b < 0 || tex->b > 255)
		return (TEX_ERR_COLOR_RANGE);
	tex->set = 1;
	return (0);
}

static int	set_texture_path(char **dest, char *line, int offset)
{
	char	*path;
	int		err;

	if (*dest)
		return (TEX_ERR_DUPLICATE);
	path = extract_path(line + offset);
	if (!path)
		return (TEX_ERR_MISSING_PATH);
	err = validate_texture_file(path);
	if (err)
	{
		free(path);
		return (err);
	}
	*dest = path;
	return (0);
}

static int	process_line(char *line, t_map *map)
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

int	parse_textures(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = 0;
	line = get_next_line(fd);
	while (line && !err)
	{
		err = process_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (err)
		print_texture_error(err);
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| !map->floor.set || !map->ceil.set)
	{
		if (!err)
			print_texture_error(TEX_ERR_MISSING_ELEMENT);
		return (1);
	}
	return (err != 0);
}
