#ifndef MAP_H
#define MAP_H

// Define error flags
#define ERR_NULL_FILENAME    (1 << 0)
#define ERR_EMPTY_STRING     (1 << 1)
#define ERR_TOO_SHORT        (1 << 2)
#define ERR_NO_EXTENSION     (1 << 3)
#define ERR_WRONG_EXTENSION  (1 << 4)
#define ERR_ONLY_EXTENSION   (1 << 5)
#define ERR_EXT_IN_MIDDLE    (1 << 6)
#define ERR_CASE_SENSITIVE   (1 << 7)
#define ERR_TRAILING_SPACE   (1 << 8)
#define ERR_DIR_AS_FILE      (1 << 9)
#define ERR_FILE_NOT_FOUND   (1 << 10)
#define ERR_PERMISSION       (1 << 11)

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
}			t_map;

#endif

