/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_rotate_player.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com.tr>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026-02-14 14:14:54 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_vec.x;
	game->player.dir_vec.x = game->player.dir_vec.x * cos(ROT_SPEED)
		- game->player.dir_vec.y * sin(ROT_SPEED);
	game->player.dir_vec.y = old_dir_x * sin(ROT_SPEED) + game->player.dir_vec.y
		* cos(ROT_SPEED);
	old_plane_x = game->player.plane_vec.x;
	game->player.plane_vec.x = game->player.plane_vec.x * cos(ROT_SPEED)
		- game->player.plane_vec.y * sin(ROT_SPEED);
	game->player.plane_vec.y = old_plane_x * sin(ROT_SPEED)
		+ game->player.plane_vec.y * cos(ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_vec.x;
	game->player.dir_vec.x = game->player.dir_vec.x * cos(-ROT_SPEED)
		- game->player.dir_vec.y * sin(-ROT_SPEED);
	game->player.dir_vec.y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir_vec.y * cos(-ROT_SPEED);
	old_plane_x = game->player.plane_vec.x;
	game->player.plane_vec.x = game->player.plane_vec.x * cos(-ROT_SPEED)
		- game->player.plane_vec.y * sin(-ROT_SPEED);
	game->player.plane_vec.y = old_plane_x * sin(-ROT_SPEED)
		+ game->player.plane_vec.y * cos(-ROT_SPEED);
}
