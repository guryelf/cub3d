/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse_coordinator.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 00:50:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_cub_file(t_rawdata *rawdata, t_map *map)
{
	if (parse_textures(rawdata->textures, map) != 0)
	{
		free_map_data(map);
		return (1);
	}
	if (parse_colors(rawdata->colors, map) != 0)
	{
		free_map_data(map);
		return (1);
	}
	if (normalize_map_grid(rawdata->grid) != 0)
	{
		free_map_data(map);
		return (1);
	}
	if (parse_map_grid(rawdata->grid, map) != 0)
	{
		free_map_data(map);
		return (1);
	}
	return (0);
}
