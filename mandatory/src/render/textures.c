/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 00:00:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (load_single_texture(game, &game->textures[0], game->map.no_path) != 0)
		return (1);
	if (load_single_texture(game, &game->textures[1], game->map.so_path) != 0)
		return (1);
	if (load_single_texture(game, &game->textures[2], game->map.we_path) != 0)
		return (1);
	if (load_single_texture(game, &game->textures[3], game->map.ea_path) != 0)
		return (1);
	return (0);
}
