/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_file_ending.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 05:10:46 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/error.h"
#include "../../../inc/get_next_line.h"
#include "../../../inc/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*get_last_line(int fd)
{
	char	*line;
	char	*last_line;

	last_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (last_line)
			free(last_line);
		last_line = line;
		line = get_next_line(fd);
	}
	return (last_line);
}

int	file_ends_with_next_line(const char *file_path)
{
	int		fd;
	char	*last_line;
	int		result;
	size_t	len;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	last_line = get_last_line(fd);
	close(fd);
	result = 0;
	if (last_line)
	{
		len = ft_strlen(last_line);
		if (len > 0 && last_line[len - 1] == '\n')
			result = 1;
		free(last_line);
	}
	return (result);
}
