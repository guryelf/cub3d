/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 05:10:01 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"

char	*extract_path(char *line)
{
	char	*path;
	char	*end;
	int		len;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line || *line == '\n')
		return (NULL);
	end = line;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	len = end - line;
	path = ft_substr(line, 0, len);
	return (path);
}

int	validate_texture_file(const char *path)
{
	int	fd;
	int	len;

	if (!path || !*path)
		return (TEX_ERR_MISSING_PATH);
	len = ft_strlen(path);
	if (len < 5)
		return (TEX_ERR_MISSING_PATH);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (TEX_ERR_INVALID_ID);
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (ERR_IS_DIRECTORY);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (TEX_ERR_OPEN_FAILED);
	close(fd);
	return (0);
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
