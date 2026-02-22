/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_validate_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:25:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:50:43 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_path(char *line)
{
	char	*end;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	if (!*line || *line == '\n')
		return (NULL);
	end = line;
	while (*end && *end != ' ' && *end != '\n')
		end++;
	return (ft_substr(line, 0, end - line));
}

char	**append_line(char **arr, char *line)
{
	int		size;
	char	**new_arr;
	int		i;

	size = 0;
	if (arr)
	{
		while (arr[size])
			size++;
	}
	new_arr = ft_calloc(size + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = line;
	free(arr);
	return (new_arr);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| is_player_char(c) || c == '\n');
}
