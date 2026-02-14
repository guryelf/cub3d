/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_key_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com.tr>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026-02-14 14:14:54 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map.height || map_x < 0)
		return (1);
	if (map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_vec.x + game->player.dir_vec.x * MOVE_SPEED;
	new_y = game->player.pos_vec.y + game->player.dir_vec.y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.pos_vec.y))
		game->player.pos_vec.x = new_x;
	if (!is_wall(game, game->player.pos_vec.x, new_y))
		game->player.pos_vec.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_vec.x - game->player.dir_vec.x * MOVE_SPEED;
	new_y = game->player.pos_vec.y - game->player.dir_vec.y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.pos_vec.y))
		game->player.pos_vec.x = new_x;
	if (!is_wall(game, game->player.pos_vec.x, new_y))
		game->player.pos_vec.y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_vec.x - game->player.plane_vec.x * MOVE_SPEED;
	new_y = game->player.pos_vec.y - game->player.plane_vec.y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.pos_vec.y))
		game->player.pos_vec.x = new_x;
	if (!is_wall(game, game->player.pos_vec.x, new_y))
		game->player.pos_vec.y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_vec.x + game->player.plane_vec.x * MOVE_SPEED;
	new_y = game->player.pos_vec.y + game->player.plane_vec.y * MOVE_SPEED;
	if (!is_wall(game, new_x, game->player.pos_vec.y))
		game->player.pos_vec.x = new_x;
	if (!is_wall(game, game->player.pos_vec.x, new_y))
		game->player.pos_vec.y = new_y;
}
