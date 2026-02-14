/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:13 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 00:35:59 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define _GNU_SOURCE
# include <fcntl.h>
# include <stdint.h>
# include <unistd.h>

typedef enum e_error
{
	ERR_NULL_FILENAME,
	ERR_EMPTY_STRING,
	ERR_TOO_SHORT,
	ERR_NO_EXTENSION,
	ERR_WRONG_EXTENSION,
	ERR_ONLY_EXTENSION,
	ERR_TRAILING_SPACE,
	ERR_IS_DIRECTORY,
	ERR_OPEN_FAILED,
	TEX_ERR_INVALID_ID,
	TEX_ERR_MISSING_PATH,
	TEX_ERR_DUPLICATE,
	TEX_ERR_OPEN_FAILED,
	TEX_ERR_INVALID_COLOR,
	TEX_ERR_COLOR_RANGE,
	TEX_ERR_MISSING_ELEMENT
}	t_error;

void	print_file_parsing_error(t_error error);
void	print_texture_error(t_error error);

#endif