/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 04:47:56 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "map.h"
#include "get_next_line.h"

char	*skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

char	*extract_path(char *line)
{
	char	*path;
	char	*end;
	int		len;

	line = skip_spaces(line);
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
	line = skip_spaces(line);
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

void	print_texture_error(int error)
{
	const char	*msg;

	if (error == TEX_ERR_INVALID_ID)
		msg = "Error: Invalid texture identifier or extension\n";
	else if (error == TEX_ERR_MISSING_PATH)
		msg = "Error: Missing texture path\n";
	else if (error == TEX_ERR_DUPLICATE)
		msg = "Error: Duplicate texture/color definition\n";
	else if (error == TEX_ERR_OPEN_FAILED)
		msg = "Error: Cannot open texture file\n";
	else if (error == TEX_ERR_INVALID_COLOR)
		msg = "Error: Invalid color format (use R,G,B)\n";
	else if (error == TEX_ERR_COLOR_RANGE)
		msg = "Error: Color values must be 0-255\n";
	else if (error == TEX_ERR_MISSING_ELEMENT)
		msg = "Error: Missing texture or color element\n";
	else if (error == ERR_IS_DIRECTORY)
		msg = "Error: Texture path is a directory\n";
	else
		msg = "Error: Unknown texture parsing error\n";
	write(2, msg, ft_strlen(msg));
}
