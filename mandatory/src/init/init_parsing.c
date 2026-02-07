/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:12 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 04:32:13 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"

int	init_parsing(const char *file_path, t_map *map)
{
	int	fd;

	if (parse_file(file_path) != 0)
		return (1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_textures(fd, map) != 0)
	{
		close(fd);
		return (1);
	}
	if (parse_map(fd, map) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (check_map(map) != 0)
		return (1);
	return (0);
}
