#include "../../inc/cub3d.h"

int	game_loop(t_game *game)
{
	render_frame(game);
	return (0);
}

int	handle_close(t_game *game)
{
	clean_exit(game);
	return (0);
}

void	start_game(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_loop(game->mlx);
}
