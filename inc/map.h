/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:25 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 09:06:47 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "error.h"
# include "get_next_line.h"
# include "libft.h"
# include "texture.h"

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_texture	floor;
	t_texture	ceil;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

char			*skip_spaces(char *line);
char			*extract_path(char *line);
int				validate_texture_file(const char *path);
int				parse_file(const char *file_path);
int				parse_textures(const char *file_path, t_map *map);
int				set_texture_path(char **dest, char *line, int offset);
int				parse_color_values(char *line, t_texture *tex);
int				read_map_grid(const char *file_path, t_map *map);
int				is_empty_line(char *line);
int				is_texture_or_color_line(char *line);
char			*parse_map_line(char *line);
int				process_lines_loop(int fd, t_map *map, char *first_line);
int				validate_map(t_map *map);
int			normalize_map_grid(t_map *map);
int				validate_enclosure(t_map *map);
int				check_zeros_enclosure(t_map *map);
int				validate_mapfile(const char *file_path);
int				dispatch_sneaky_files(const char *file_path);
int				parse_mapfile(const char *file_path, t_map *map);
void			free_map_data(t_map *map);
int				is_blank_line(const char *line);
int				is_valid_identifier(const char *line);
int				validate_line_format(const char *line);
void			consume_remaining_lines(int fd);

#endif
