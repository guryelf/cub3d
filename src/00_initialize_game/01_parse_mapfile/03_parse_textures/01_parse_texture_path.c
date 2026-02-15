/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parse_texture_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:40:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 17:40:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*extract_path(char *line)
{
	char	*path;
	char	*end;
	int		len;

	while (*line && (*line == ' '))
		line++;
	if (!*line || *line == '\n')
		return (NULL);
	end = line;
	while (*end && *end != ' ' && *end != '\n')
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

int	set_texture_path(char **dest, char *line, int offset)
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
