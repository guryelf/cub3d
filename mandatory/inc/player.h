#ifndef PLAYER_H
# define PLAYER_H

# include <unistd.h>
#include "vector2.h"

typedef struct s_player
{
	t_vec2	pos_vec;
	t_vec2	dir_vec;
	t_vec2	plane_vec;
	float     pos_x;
	float     pos_y;
	float     dir_x;
	float     dir_y;
	float     plane_x;
	float     plane_y;
	
}			t_player;

#endif
