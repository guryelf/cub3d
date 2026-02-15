/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_file_ending.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 04:56:04 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/error.h"
#include <fcntl.h>
#include <unistd.h>

static int	get_file_size(int fd)
{
	int		size;
	char	c;

	size = 0;
	while (read(fd, &c, 1) > 0)
		size++;
	return (size);
}

int	file_ends_with_next_line(const char *file_path)
{
	int		fd;
	int		size;
	char	last_char;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	size = get_file_size(fd);
	close(fd);
	if (size == 0)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	lseek(fd, size - 1, SEEK_SET);
	if (read(fd, &last_char, 1) <= 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (last_char == '\n')
		return (1);
	return (0);
}

int	validate_file_ending(const char *file_path)
{
	if (file_ends_with_next_line(file_path))
	{
		write(2, "Error: File ends with a newline\n", 33);
		return (1);
	}
	return (0);
}
