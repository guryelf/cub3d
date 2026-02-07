/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:24 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 04:32:31 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

static int	validate_filename(const char *path)
{
	int	len;

	if (!path)
		return (ERR_NULL_FILENAME);
	if (!*path)
		return (ERR_EMPTY_STRING);
	len = ft_strlen(path);
	if (len < 5)
		return (ERR_TOO_SHORT);
	if (path[len - 1] == ' ')
		return (ERR_TRAILING_SPACE);
	return (check_extension(path, len));
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

static void	print_error(int error)
{
	const char	*msg;

	if (error == ERR_NULL_FILENAME)
		msg = "Error: NULL filename\n";
	else if (error == ERR_EMPTY_STRING)
		msg = "Error: Empty filename\n";
	else if (error == ERR_TOO_SHORT)
		msg = "Error: Filename too short\n";
	else if (error == ERR_TRAILING_SPACE)
		msg = "Error: Filename has trailing spaces\n";
	else if (error == ERR_CASE_SENSITIVE)
		msg = "Error: Extension must be lowercase .cub\n";
	else if (error == ERR_WRONG_EXTENSION)
		msg = "Error: Wrong extension (must be .cub)\n";
	else if (error == ERR_IS_DIRECTORY)
		msg = "Error: Path is a directory\n";
	else
		msg = "Error: Cannot open file\n";
	write(2, msg, ft_strlen(msg));
}

int	parse_file(const char *file_path)
{
	int	error;

	error = validate_filename(file_path);
	if (!error)
		error = validate_file_access(file_path);
	if (error)
	{
		print_error(error);
		return (1);
	}
	return (0);
}
