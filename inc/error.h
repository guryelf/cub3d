/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:13 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 09:53:04 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define _GNU_SOURCE
# include <fcntl.h>
# include <stdint.h>
# include <unistd.h>

// Error messages
# define MSG_MAP_READING "Failed to read map"
# define MSG_MAP_VALIDATION "Map validation failed"
# define MSG_TEXTURE_PARSING "Failed to parse textures"
# define MSG_MISSING_TEXTURE "Missing texture or color element"
# define MSG_SNEAKY_FILE "Invalid file structure"
# define MSG_FILE_NEWLINE "File ends with newline"
# define MSG_EMPTY_STRING "Empty filename"
# define MSG_NO_EXTENSION "Filename has no extension"
# define MSG_WRONG_EXTENSION "Wrong extension (must be .cub)"
# define MSG_ONLY_EXTENSION "Filename cannot start with a dot"
# define MSG_IS_DIRECTORY "Path is a directory"
# define MSG_OPEN_FAILED "Cannot open file"
# define MSG_INVALID_TEXTURE_ID "Invalid texture identifier"
# define MSG_MISSING_TEXTURE_PATH "Missing texture path"
# define MSG_DUPLICATE_TEXTURE "Duplicate texture/color definition"
# define MSG_TEXTURE_FILE_OPEN "Cannot open texture file"
# define MSG_INVALID_COLOR "Invalid color format (use R,G,B)"
# define MSG_COLOR_RANGE "Color values must be 0-255"

void	print_error(const char *msg);
int		file_ends_with_next_line(const char *file_path);

#endif