/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_validate_coordinator.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by rakman            #+#    #+#             */
/*   Updated: 2026/02/21 11:15:00 by rakman           ###   ########.fr       */
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

t_rawdata	*validate_cub_file(const char *file_path)
{
	t_rawdata	*raw_data;

	if (validate_filename(file_path) != 0)
		return (NULL);
	if (validate_file_access(file_path) != 0)
		return (NULL);
	raw_data = ft_calloc(1, sizeof(t_rawdata));
	if (!raw_data)
		return (NULL);
	if (populate_rawdata(file_path, raw_data) == NULL)
		return (NULL);
	if (validate_rawfiledata_configs(raw_data) != 0)
	{
		free_rawdata(raw_data);
		return (NULL);
	}
	return (raw_data);
}
