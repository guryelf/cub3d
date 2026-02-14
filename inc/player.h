/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:28 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 19:08:39 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <unistd.h>
# include "vector2.h"

typedef struct s_player
{
	t_vec2	pos_vec;
	t_vec2	dir_vec;
	t_vec2	plane_vec;
}			t_player;

#endif