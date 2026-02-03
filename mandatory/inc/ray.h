#ifndef RAY_H
#define RAY_H

#include <unistd.h>
#include "vector2.h"


typedef struct s_ray
{
	t_vec2	camera_vec;
	t_vec2	ray_dir_vec;
	t_vec2	map_vec;
	t_vec2	side_dist_vec;
	t_vec2	delta_dist_vec;
	t_vec2	step_vec;
	double	perp_wall_dist;
	int		hit;
	int		side;
	int		line_height;
}			t_ray;



#endif