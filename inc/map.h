/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:08:25 by rakman            #+#    #+#             */
/*   Updated: 2026/02/15 10:09:59 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "error.h"
# include "get_next_line.h"
# include "libft.h"
# include "texture.h"

typedef struct s_rawfiledata
{
	char	**textures;
	char	**colors;
	char	**grid;
}	t_rawdata;

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
}	t_map;

char		*skip_spaces(char *line);
char		*extract_path(char *line);
int			count_lines(char **arr);
int			count_words(const char *line);
int			validate_texture_file(const char *path);
int			parse_file(const char *file_path);
void		free_map_data(t_map *map);
t_rawdata	*populate_rawdata(const char *file_path, t_rawdata *rawdata);
void		free_rawdata(t_rawdata *rawdata);
int			is_texture_or_color_line(char *line);
char		*parse_map_line(char *line);
int			process_lines_loop(int fd, t_map *map, char *first_line);
int			validate_map_grid(t_rawdata *rawdata);
int			normalize_map_grid(char **grid);
int			parse_textures(char **textures, t_map *map);
int			parse_colors(char **colors, t_map *map);
int			parse_map_grid(char **grid, t_map *map);
int			parse_cub_file(t_rawdata *rawdata, t_map *map);
char		**append_line(char **arr, char *line);
t_rawdata	*validate_cub_file(const char *file_path);
int			validate_rawfiledata_configs(t_rawdata *rawdata);
int			is_enclosed_by_walls(t_map *tempmap);
int			has_double_map(t_map *tempmap);
int			is_blank_line(const char *line);
int			is_valid_texture_line(const char *line);
int			is_valid_color_line(const char *line);
int			is_player_char(char c);
int			is_valid_char(char c);
void		consume_remaining_lines(int fd);

#endif
