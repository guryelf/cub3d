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

static void	free_loaded_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

int	load_textures(t_game *game)
{
	if (load_single_texture(game, &game->textures[0], game->map.no_path))
		return (free_loaded_textures(game), 1);
	if (load_single_texture(game, &game->textures[1], game->map.so_path))
		return (free_loaded_textures(game), 1);
	if (load_single_texture(game, &game->textures[2], game->map.we_path))
		return (free_loaded_textures(game), 1);
	if (load_single_texture(game, &game->textures[3], game->map.ea_path))
		return (free_loaded_textures(game), 1);
	return (0);
}

