#include "cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		clean_exit(game);
	else if (keycode == 119)
		move_forward(game);
	else if (keycode == 115)
		move_backward(game);
	else if (keycode == 97)
		move_left(game);
	else if (keycode == 100)
		move_right(game);
	else if (keycode == 65361)
		rotate_right(game);
	else if (keycode == 65363)
		rotate_left(game);
	return (0);
}
