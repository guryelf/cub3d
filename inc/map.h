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
int				get_texture_type(char *line);
int				parse_file(const char *file_path);
int				parse_textures(const char *file_path, t_map *map);
int				parse_color_values(char *line, t_texture *tex);
int				parse_map(const char *file_path, t_map *map);
int				is_map_line(char *line);
char			*parse_map_line(char *line);
int				process_grid_line(char *line, t_map *map, int *i, int *in_map);
int				read_map_grid(const char *file_path, t_map *map);
int				check_map(t_map *map);
int				init_parsing(const char *file_path, t_map *map);
void			free_map_data(t_map *map);

#endif
