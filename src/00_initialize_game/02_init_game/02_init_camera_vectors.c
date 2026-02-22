/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 23:43:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/22 23:37:58 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction_north(t_player *player)
{
	player->dir_vec.x = 0;
	player->dir_vec.y = -1;
	player->plane_vec.x = 0.66;
	player->plane_vec.y = 0;
}

static void	set_direction_south(t_player *player)
{
	player->dir_vec.x = 0;
	player->dir_vec.y = 1;
	player->plane_vec.x = -0.66;
	player->plane_vec.y = 0;
}

static void	set_direction_east(t_player *player)
{
	player->dir_vec.x = 1;
	player->dir_vec.y = 0;
	player->plane_vec.x = 0;
	player->plane_vec.y = 0.66;
}

static void	set_direction_west(t_player *player)
{
	player->dir_vec.x = -1;
	player->dir_vec.y = 0;
	player->plane_vec.x = 0;
	player->plane_vec.y = -0.66;
}

int	init_camera_vectors(t_game *game)
{
	game->player.pos_vec.x = (double)game->map.player_x + 0.5;
	game->player.pos_vec.y = (double)game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
		set_direction_north(&game->player);
	else if (game->map.player_dir == 'S')
		set_direction_south(&game->player);
	else if (game->map.player_dir == 'E')
		set_direction_east(&game->player);
	else if (game->map.player_dir == 'W')
		set_direction_west(&game->player);
	return (0);
}
