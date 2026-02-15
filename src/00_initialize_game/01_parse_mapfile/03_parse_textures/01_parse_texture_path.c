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
		return (print_error(MSG_MISSING_TEXTURE_PATH), 1);
	len = ft_strlen(path);
	if (len < 5)
		return (print_error(MSG_MISSING_TEXTURE_PATH), 1);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (print_error(MSG_INVALID_TEXTURE_ID), 1);
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (print_error(MSG_IS_DIRECTORY), 1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error(MSG_TEXTURE_FILE_OPEN), 1);
	close(fd);
	return (0);
}

int	set_texture_path(char **dest, char *line, int offset)
{
	char	*path;

	if (*dest)
		return (print_error(MSG_DUPLICATE_TEXTURE), 1);
	path = extract_path(line + offset);
	if (!path)
		return (print_error(MSG_MISSING_TEXTURE_PATH), 1);
	if (validate_texture_file(path) != 0)
		return (free(path), 1);
	*dest = path;
	return (0);
}
