/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_validate_config_arrays.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 02:22:55 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:47:18 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_rawdata(t_rawdata *rawdata)
{
	if (!rawdata)
		return ;
	free_str_array(rawdata->textures);
	free_str_array(rawdata->colors);
	free_str_array(rawdata->grid);
	free(rawdata);
}

void	consume_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	validate_rawfiledata_configs(t_rawdata *rawdata)
{
	int	i;

	if (!rawdata || !rawdata->textures || !rawdata->colors)
		return (1);
	i = 0;
	while (rawdata->textures[i])
	{
		if (is_valid_texture_line(rawdata->textures[i]))
			return (1);
		i++;
	}
	i = 0;
	while (rawdata->colors[i])
	{
		if (is_valid_color_line(rawdata->colors[i]))
			return (1);
		i++;
	}
	return (0);
}
