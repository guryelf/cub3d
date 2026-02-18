/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_validate_mapfile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 00:40:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_extension(const char *basename)
{
	const char	*ext;

	if (basename[0] == '.')
		return (print_error(MSG_ONLY_EXTENSION), 1);
	ext = ft_strrchr(basename, '.');
	if (!ext)
		return (print_error(MSG_NO_EXTENSION), 1);
	if (ft_strncmp(ext, ".cub", 5) != 0)
		return (print_error(MSG_WRONG_EXTENSION), 1);
	return (0);
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
		return (print_error(MSG_OPEN_FAILED), 1);
	close(fd);
	return (0);
}

static int	validate_filename(const char *path)
{
	const char	*basename;
	const char	*slash;

	if (*path == '\0')
		return (print_error(MSG_EMPTY_STRING), 1);
	slash = ft_strrchr(path, '/');
	if (slash)
		basename = slash + 1;
	else
		basename = path;
	return (check_extension(basename));
}

int	validate_mapfile(const char *file_path)
{
	if (validate_filename(file_path) != 0)
		return (1);
	if (validate_file_access(file_path) != 0)
		return (1);
	if (dispatch_sneaky_files(file_path) != 0)
		return (1);
	if (file_ends_with_next_line(file_path) != 0)
		return (1);
	if (file_has_double_map(file_path) != 0)
		return (1);
	return (0);
}
