/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_load_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 01:01:16 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	load_single_texture(t_game *game, t_img *texture, char *path)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!texture->img)
		return (1);
	texture->addr = (int *)mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->line_len, &texture->endian);
	if (!texture->addr)
		return (1);
	return (0);
}

int	load_textures(t_game *game)
{
	t_img	*north_texture;
	t_img	*south_texture;
	t_img	*west_texture;
	t_img	*east_texture;

	north_texture = &game->textures[0];
	south_texture = &game->textures[1];
	west_texture = &game->textures[2];
	east_texture = &game->textures[3];
	if (load_single_texture(game, north_texture, game->map.no_path))
		return (1);
	if (load_single_texture(game, south_texture, game->map.so_path))
		return (1);
	if (load_single_texture(game, west_texture, game->map.we_path))
		return (1);
	if (load_single_texture(game, east_texture, game->map.ea_path))
		return (1);
	return (0);
}
