/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:14:54 by fguryel           #+#    #+#             */
/*   Updated: 2026/02/15 09:38:12 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_error(t_error error)
{
	const char	*messages[] = {
		[ERR_INVALID_CONFIG] = "Invalid configuration section",
		[ERR_INVALID_MAP_SECTION] = "Invalid map section",
		[ERR_MAP_READING_FAILED] = "Failed to read map",
		[ERR_MAP_VALIDATION_FAILED] = "Map validation failed",
		[ERR_TEXTURE_PARSING_FAILED] = "Failed to parse textures",
		[TEX_ERR_MISSING_ELEMENT] = "Missing texture or color element",
		[TEX_ERR_INVALID_COLOR] = "Invalid color format (use R,G,B)",
		[TEX_ERR_COLOR_RANGE] = "Color values must be 0-255",
		[TEX_ERR_DUPLICATE] = "Duplicate texture/color definition",
		[TEX_ERR_OPEN_FAILED] = "Cannot open texture file",
		[TEX_ERR_MISSING_PATH] = "Missing texture path",
		[TEX_ERR_INVALID_ID] = "Invalid texture identifier",
		[ERR_IS_DIRECTORY] = "Path is a directory",
		[ERR_OPEN_FAILED] = "Cannot open file",
		[ERR_WRONG_EXTENSION] = "Wrong extension (must be .cub)",
		[ERR_NO_EXTENSION] = "Filename has no extension",
		[ERR_ONLY_EXTENSION] = "Filename cannot start with a dot",
		[ERR_TOO_SHORT] = "Filename too short",
		[ERR_EMPTY_STRING] = "Empty filename",
		[ERR_TRAILING_SPACE] = "Filename has trailing spaces",
		[MAP_ERR_SNEAKY_FILE] = "Invalid file structure",
		[ERR_END_WITH_NEWLINE] = "File ends with newline"
	};

	write(2, "Error\n", 6);
	if (error < sizeof(messages) / sizeof(messages[0]) && messages[error])
	{
		write(2, messages[error], ft_strlen(messages[error]));
		write(2, "\n", 1);
	}
	else
		write(2, "Unknown error\n", 14);
}

void	print_file_parsing_error(t_error error)
{
	const char	*msg;

	if (error == ERR_EMPTY_STRING)
		msg = "Error: Empty filename\n";
	else if (error == ERR_TOO_SHORT)
		msg = "Error: Filename too short\n";
	else if (error == ERR_NO_EXTENSION)
		msg = "Error: Filename has no extension\n";
	else if (error == ERR_WRONG_EXTENSION)
		msg = "Error: Wrong extension (must be .cub)\n";
	else if (error == ERR_ONLY_EXTENSION)
		msg = "Error: Filename cannot start with a dot\n";
	else if (error == ERR_TRAILING_SPACE)
		msg = "Error: Filename has trailing spaces\n";
	else if (error == ERR_IS_DIRECTORY)
		msg = "Error: Path is a directory\n";
	else if (error == ERR_END_WITH_NEWLINE)
		msg = "Error: File ends with a newline character\n";
	else if (error == MAP_ERR_SNEAKY_FILE)
		msg = "Error: Sneaky file detected (too short or invalid content)\n";
	else
		msg = "Error: Cannot open file\n";
	write(2, msg, ft_strlen(msg));
}

void	print_texture_error(t_error error)
{
	const char	*msg;

	if (error == TEX_ERR_INVALID_ID)
		msg = "Error: Invalid texture identifier or extension\n";
	else if (error == TEX_ERR_MISSING_PATH)
		msg = "Error: Missing texture path\n";
	else if (error == TEX_ERR_DUPLICATE)
		msg = "Error: Duplicate texture/color definition\n";
	else if (error == TEX_ERR_OPEN_FAILED)
		msg = "Error: Cannot open texture file\n";
	else if (error == TEX_ERR_INVALID_COLOR)
		msg = "Error: Invalid color format (use R,G,B)\n";
	else if (error == TEX_ERR_COLOR_RANGE)
		msg = "Error: Color values must be 0-255\n";
	else if (error == TEX_ERR_MISSING_ELEMENT)
		msg = "Error: Missing texture or color element\n";
	else if (error == ERR_IS_DIRECTORY)
		msg = "Error: Texture path is a directory\n";
	else
		msg = "Error: Unknown texture parsing error\n";
	write(2, msg, ft_strlen(msg));
}
