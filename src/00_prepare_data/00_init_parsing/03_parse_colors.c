/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:10:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 22:07:43 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	validate_color_range(t_texture *tex)
{
	if (tex->r < 0 || tex->r > 255)
		return (TEX_ERR_COLOR_RANGE);
	if (tex->g < 0 || tex->g > 255)
		return (TEX_ERR_COLOR_RANGE);
	if (tex->b < 0 || tex->b > 255)
		return (TEX_ERR_COLOR_RANGE);
	return (0);
}

static int	parse_rgb_values(char **split, t_texture *tex)
{
	int	i;

	tex->r = ft_atoi(split[0]);
	tex->g = ft_atoi(split[1]);
	tex->b = ft_atoi(split[2]);
	i = 0;
	while (i < 3)
		free(split[i++]);
	free(split);
	if (validate_color_range(tex))
		return (TEX_ERR_COLOR_RANGE);
	tex->set = 1;
	return (0);
}

int	parse_color_values(char *line, t_texture *tex)
{
	char	**split;
	int		i;

	if (tex->set)
		return (TEX_ERR_DUPLICATE);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (TEX_ERR_INVALID_COLOR);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		while (--i >= 0)
			free(split[i]);
		free(split);
		return (TEX_ERR_INVALID_COLOR);
	}
	return (parse_rgb_values(split, tex));
}
