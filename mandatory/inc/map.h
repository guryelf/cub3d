#ifndef MAP_H
# define MAP_H

# define _GNU_SOURCE
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>

# define ERR_NULL_FILENAME    (1 << 0)
# define ERR_EMPTY_STRING     (1 << 1)
# define ERR_TOO_SHORT        (1 << 2)
# define ERR_WRONG_EXTENSION  (1 << 3)
# define ERR_ONLY_EXTENSION   (1 << 4)
# define ERR_CASE_SENSITIVE   (1 << 5)
# define ERR_TRAILING_SPACE   (1 << 6)
# define ERR_IS_DIRECTORY     (1 << 7)
# define ERR_OPEN_FAILED      (1 << 8)

# define TEX_ERR_INVALID_ID      (1 << 9)
# define TEX_ERR_MISSING_PATH    (1 << 10)
# define TEX_ERR_DUPLICATE       (1 << 11)
# define TEX_ERR_OPEN_FAILED     (1 << 12)
# define TEX_ERR_INVALID_COLOR   (1 << 13)
# define TEX_ERR_COLOR_RANGE     (1 << 14)
# define TEX_ERR_MISSING_ELEMENT (1 << 15)

# include "libft.h"

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	int		floor_set;
	int		ceil_set;
}			t_map;

int	parse_file(const char *file_path);
int	parse_textures(const char *file_path, t_map *map);

#endif


