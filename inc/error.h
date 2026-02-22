/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:13 by rakman            #+#    #+#             */
/*   Updated: 2026/02/21 13:00:00 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define _GNU_SOURCE
# include <fcntl.h>
# include <stdint.h>
# include <unistd.h>

# define MSG_MAP_NOT_ENCLOSED "Map is not enclosed by walls"
# define MSG_INVALID_MAP_CHAR "Invalid character in map"
# define MSG_NO_PLAYER "No player found in map"
# define MSG_MULTIPLE_PLAYERS "Multiple players found in map"
# define MSG_EMPTY_MAP "Map is empty"
# define MSG_MISSING_TEXTURE_ID "Missing texture identifier"
# define MSG_MISSING_COLOR_ID "Missing color identifier"
# define MSG_MISSING_MAP_GRID "Missing map grid"
# define MSG_MISSING_BLANK_LINE "Missing blank line after configs"
# define MSG_EMPTY_STRING "Empty filename"
# define MSG_NO_EXTENSION "Filename has no extension"
# define MSG_WRONG_EXTENSION "Wrong extension (must be .cub)"
# define MSG_ONLY_EXTENSION "Filename cannot start with a dot"
# define MSG_IS_DIRECTORY "Path is a directory"
# define MSG_OPEN_FAILED "Cannot open file"
# define MSG_INVALID_CONFIG "Invalid configuration element"
# define MSG_INVALID_TEXTCONFIG "Invalid texture configuration"
# define MSG_INVALID_COLOR_CONFIG "Invalid color configuration"
# define MSG_MISSING_TEXTURE_PATH "Missing texture path"
# define MSG_INVALID_TEXTURE_LINE "Invalid texture line format"
# define MSG_DUPLICATE_TEXTURE "Duplicate texture/color definition"
# define MSG_TEXTURE_FILE_OPEN "Cannot open texture file"
# define MSG_INVALID_COLOR "Invalid color format (use R,G,B)"
# define MSG_COLOR_RANGE "Color values must be 0-255"
# define MSG_INVALID_TEXTURE_EXTENSION "Texture must end with .xpm"
# define MSG_DOUBLE_MAP "Map has unreachable sections (double map)"
# define MSG_MLX_INIT "MLX initialization failed"
# define MSG_TEXTURE_LOAD "Texture loading failed"
# define MSG_WINDOW_INIT "MLX window initialization failed"
# define MSG_DATA_INIT "Data initialization failed"

void	print_error(const char *msg);
int		file_ends_with_next_line(const char *file_path);

#endif