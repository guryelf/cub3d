/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 04:48:24 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"
#include "map.h"

char		*skip_spaces(char *line);
char		*extract_path(char *line);
int			validate_texture_file(const char *path);
int			get_texture_type(char *line);
void		print_texture_error(int error);

static void	free_split(char **split, int count)
{
	while (--count >= 0)
		free(split[count]);
	free(split);
}

static int	parse_color_values(char *line, int *r, int *g, int *b)
{
	char	**split;
	int		i;

	line = skip_spaces(line);
	split = ft_split(line, ',');
	if (!split)
		return (TEX_ERR_INVALID_COLOR);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split(split, i);
		return (TEX_ERR_INVALID_COLOR);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_split(split, 3);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (TEX_ERR_COLOR_RANGE);
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

static int	set_color(t_map *map, char *line, int type)
{
	int	err;

	if (type == 5)
	{
		if (map->floor_set)
			return (TEX_ERR_DUPLICATE);
		err = parse_color_values(line + 2, &map->floor_r, &map->floor_g,
				&map->floor_b);
		if (!err)
			map->floor_set = 1;
	}
	else
	{
		if (map->ceil_set)
			return (TEX_ERR_DUPLICATE);
		err = parse_color_values(line + 2, &map->ceil_r, &map->ceil_g,
				&map->ceil_b);
		if (!err)
			map->ceil_set = 1;
	}
	return (err);
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
	return (set_color(map, line, type));
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
		|| !map->floor_set || !map->ceil_set)
	{
		if (!err)
			print_texture_error(TEX_ERR_MISSING_ELEMENT);
		return (1);
	}
	return (err != 0);
}
