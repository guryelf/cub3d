/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by rakman            #+#    #+#             */
/*   Updated: 2026/02/13 19:42:36 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/cub3d.h"

int	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(&game->ray, &game->player, x);
		perform_dda(&game->ray, &game->map, &game->player);
		calculate_wall(&game->ray, &game->player);
		draw_background(game, x, &game->ray);
		draw_textured_wall(game, x, &game->ray);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
