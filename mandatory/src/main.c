/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguryel <fguryel@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 04:32:15 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/07 05:18:53 by fguryel          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	if (init_parsing(argv[1], &map) != 0)
		return (1);
	return (0);
}