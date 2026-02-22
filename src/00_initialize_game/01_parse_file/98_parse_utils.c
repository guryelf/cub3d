/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_extract_raw_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:42:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/21 11:50:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *line)
{
	if (!line)
		return (NULL);
	while (*line && *line == ' ')
		line++;
	return (line);
}
