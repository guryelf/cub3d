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

# include "libft.h"

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
}			t_map;

int	parse_file(const char *file_path);

#endif

