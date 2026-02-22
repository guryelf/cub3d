/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/15 09:38:12 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game		game;
	t_rawdata	*rawdata;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	rawdata = validate_cub_file(argv[1]);
	if (rawdata == NULL)
		return (1);
	if (parse_cub_file(rawdata, &game.map) != 0)
		return (free_rawdata(rawdata), free_map_data(&game.map), 1);
	if (init_game_resources(&game) != 0)
		return (free_rawdata(rawdata), free_map_data(&game.map), 1);
	free_rawdata(rawdata);
	start_game(&game);
	return (0);
}
