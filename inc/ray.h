/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:33 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 19:08:39 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <unistd.h>
# include "vector2.h"

typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_num;
}			t_ray;

void	setup_ray(t_ray *ray, t_player *player, int x);
void	perform_dda(t_ray *ray, t_map *map, t_player *player);
void	calculate_wall(t_ray *ray, t_player *player);

#endif