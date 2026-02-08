/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/08 18:49:27 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	if (init_parsing(argv[1], &game.map) != 0)
		return (1);
	
	// TODO: Add initialization for other game components
	// For now, just return success after parsing
	write(1, "Parsing successful! Ready for game initialization.\n", 52);
	return (0);
}