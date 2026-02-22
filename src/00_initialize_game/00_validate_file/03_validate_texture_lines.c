/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_validate_texture_lines.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 22:46:11 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(const char *basename)
{
	const char	*ext;

	if (basename[0] == '.')
		return (print_error(MSG_ONLY_EXTENSION), 1);
	ext = ft_strrchr(basename, '.');
	if (!ext)
		return (print_error(MSG_NO_EXTENSION), 1);
	if (ft_strncmp(ext, ".xpm", 5) != 0)
		return (print_error(MSG_INVALID_TEXTURE_EXTENSION), 1);
	return (0);
}

static int	validate_filename(const char *path)
{
	const char	*basename;
	const char	*slash;

	slash = ft_strrchr(path, '/');
	if (slash)
		basename = slash + 1;
	else
		basename = path;
	return (check_extension(basename));
}

static int	validate_file_access(const char *path)
{
	int	fd;

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

int	is_valid_texture_line(const char *line)
{
	char	*path;

	if (count_words(line) != 2)
		return (print_error(MSG_INVALID_TEXTURE_LINE), 1);
	path = extract_path((char *)line);
	if (!path)
		return (print_error(MSG_MISSING_TEXTURE_PATH), 1);
	if (validate_filename(path) != 0 || validate_file_access(path) != 0)
		return (free(path), 1);
	free(path);
	return (0);
}
