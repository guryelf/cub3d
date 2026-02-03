#ifndef MAP_H
#define MAP_H


typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int     floor_color;
	int     ceiling_color;
	char	*no_path;
	char	*so_path;
}			t_map;

#endif

