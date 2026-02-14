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

#include "map.h"

static int	check_extension(const char *path, int len)
{
	const char	*ext;
	int			i;

	ext = path + len - 4;
	if (ft_strncmp(ext, ".cub", 4) == 0)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (ft_tolower(ext[i]) != ".cub"[i])
			return (ERR_WRONG_EXTENSION);
		i++;
	}
	return (ERR_CASE_SENSITIVE);
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
	int			len;
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
	if (basename[0] == '.')
		return (ERR_ONLY_EXTENSION);
	return (check_extension(basename, len));
}

int	validate_mapfile(const char *file_path)
{
	int	error;

	error = validate_filename(file_path);
	if (!error)
		error = validate_file_access(file_path);
	if (error)
	{
		print_file_parsing_error(error);
		return (1);
	}
	return (0);
}
