#ifndef PLAYER_H
# define PLAYER_H

# include <unistd.h>
#include "vector2.h"

typedef struct s_player
{
	t_vec2	pos_vec;
	t_vec2	dir_vec;
	t_vec2	plane_vec;
}			t_player;

#endif