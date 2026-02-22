/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_populate_rawdata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:20:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:47:20 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_config_flag(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0b000001);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (0b000010);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (0b000100);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (0b001000);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (0b010000);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (0b100000);
	return (0);
}

static int	handle_config_line(t_rawdata *rawdata, char *line, int *flags)
{
	int	current_flag;

	current_flag = get_config_flag(line);
	if (current_flag == 0)
		return (print_error(MSG_INVALID_CONFIG), 1);
	if (*flags & current_flag)
		return (print_error(MSG_DUPLICATE_TEXTURE), 1);
	*flags = *flags | current_flag;
	if ((current_flag & 0b001111) != 0)
		rawdata->textures = append_line(rawdata->textures, line);
	else if ((current_flag & 0b110000) != 0)
		rawdata->colors = append_line(rawdata->colors, line);
	return (0);
}

static int	read_grid(int fd, t_rawdata *rawdata)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (print_error(MSG_MISSING_MAP_GRID), 1);
	while (line)
	{
		rawdata->grid = append_line(rawdata->grid, line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	read_configs(int fd, t_rawdata *rawdata, int *flags)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_blank_line(line))
			free(line);
		else if (handle_config_line(rawdata, line, flags) != 0)
			return (free(line), 1);
		if (*flags == 0b111111)
		{
			line = get_next_line(fd);
			if (line && !is_blank_line(line))
				return (free(line), print_error(MSG_MISSING_BLANK_LINE), 1);
			free(line);
			break ;
		}
		line = get_next_line(fd);
	}
	return (0);
}

t_rawdata	*populate_rawdata(const char *file_path, t_rawdata *rawdata)
{
	int	fd;
	int	flags;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (free(rawdata), NULL);
	flags = 0;
	if (read_configs(fd, rawdata, &flags) != 0 || read_grid(fd, rawdata) != 0)
	{
		consume_remaining_lines(fd);
		return (close(fd), free_rawdata(rawdata), NULL);
	}
	close(fd);
	if ((flags & 0b001111) != 0b001111)
		return (print_error(MSG_MISSING_TEXTURE_ID), free_rawdata(rawdata),
			NULL);
	if ((flags & 0b110000) != 0b110000)
		return (print_error(MSG_MISSING_COLOR_ID), free_rawdata(rawdata), NULL);
	if (!rawdata->grid || !rawdata->grid[0])
		return (print_error(MSG_MISSING_MAP_GRID), free_rawdata(rawdata), NULL);
	return (rawdata);
}
