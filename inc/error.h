/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:13 by rakman            #+#    #+#             */
/*   Updated: 2026/02/14 19:08:39 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define _GNU_SOURCE
# include <fcntl.h>
# include <stdint.h>
# include <unistd.h>

enum
{
	ERR_NULL_FILENAME = (1 << 0),
	ERR_EMPTY_STRING = (1 << 1),
	ERR_TOO_SHORT = (1 << 2),
	ERR_WRONG_EXTENSION = (1 << 3),
	ERR_ONLY_EXTENSION = (1 << 4),
	ERR_CASE_SENSITIVE = (1 << 5),
	ERR_TRAILING_SPACE = (1 << 6),
	ERR_IS_DIRECTORY = (1 << 7),
	ERR_OPEN_FAILED = (1 << 8),
	TEX_ERR_INVALID_ID = (1 << 9),
	TEX_ERR_MISSING_PATH = (1 << 10),
	TEX_ERR_DUPLICATE = (1 << 11),
	TEX_ERR_OPEN_FAILED = (1 << 12),
	TEX_ERR_INVALID_COLOR = (1 << 13),
	TEX_ERR_COLOR_RANGE = (1 << 14),
	TEX_ERR_MISSING_ELEMENT = (1 << 15)
};

void	print_file_parsing_error(int error);
void	print_texture_error(int error);

#endif