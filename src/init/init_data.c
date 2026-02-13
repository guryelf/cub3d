/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 19:42:36 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

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

static void	init_player(t_player *player, t_map *map)
{
	player->pos_vec.x = (double)map->player_x + 0.5;
	player->pos_vec.y = (double)map->player_y + 0.5;
	if (map->player_dir == 'N')
		set_direction_north(player);
	else if (map->player_dir == 'S')
		set_direction_south(player);
	else if (map->player_dir == 'E')
		set_direction_east(player);
	else if (map->player_dir == 'W')
		set_direction_west(player);
}

int	init_data(t_game *game)
{
	init_player(&game->player, &game->map);
	return (0);
}
