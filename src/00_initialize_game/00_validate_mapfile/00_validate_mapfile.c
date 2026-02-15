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
		return (ERR_ONLY_EXTENSION);
	ext = ft_strrchr(basename, '.');
	if (!ext)
		return (ERR_NO_EXTENSION);
	if (ft_strncmp(ext, ".cub", 5) != 0)
		return (ERR_WRONG_EXTENSION);
	return (0);
}

static int	validate_file_access(const char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (ERR_IS_DIRECTORY);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN_FAILED);
	close(fd);
	return (0);
}

static int	validate_filename(const char *path)
{
	const char	*basename;
	const char	*slash;

	if (path == NULL)
		return (ERR_NULL_FILENAME);
	if (*path == '\0')
		return (ERR_EMPTY_STRING);
	slash = ft_strrchr(path, '/');
	if (slash)
		basename = slash + 1;
	else
		basename = path;
	return (check_extension(basename));
}

int	validate_mapfile(const char *file_path)
{
	int	error;

	error = validate_filename(file_path);
	if (!error)
		error = validate_file_access(file_path);
	if (error)
		return (print_file_parsing_error(error), 1);
	if (dispatch_sneaky_files(file_path) != 0)
		return (print_file_parsing_error(MAP_ERR_SNEAKY_FILE), 1);
	if (file_ends_with_next_line(file_path))
		return (print_file_parsing_error(ERR_END_WITH_NEWLINE), 1);
	return (0);
}
