/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com.tr>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026-02-14 14:14:54 by fguryel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	setup_ray(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dir_vec.x + player->plane_vec.x * ray->camera_x;
	ray->ray_dir_y = player->dir_vec.y + player->plane_vec.y * ray->camera_x;
	ray->map_x = (int)player->pos_vec.x;
	ray->map_y = (int)player->pos_vec.y;
	ray->hit = 0;
}
