#include "map.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static bool parse_config_line(t_map *map, char *line, void *mlx)
{
    if (!line || !*line)
        return true;
    if (strncmp(line, "NO ", 3) == 0)
    {
        map->no_texture = texture_new(mlx, line + 3);
        entity_add_heap((t_entity *)map, map->no_texture);
    }
    else if (strncmp(line, "SO ", 3) == 0)
    {
        map->so_texture = texture_new(mlx, line + 3);
        entity_add_heap((t_entity *)map, map->so_texture);
    }
    else if (strncmp(line, "WE ", 3) == 0)
    {
        map->we_texture = texture_new(mlx, line + 3);
        entity_add_heap((t_entity *)map, map->we_texture);
    }
    else if (strncmp(line, "EA ", 3) == 0)
    {
        map->ea_texture = texture_new(mlx, line + 3);
        entity_add_heap((t_entity *)map, map->ea_texture);
    }
    else if (strncmp(line, "F ", 2) == 0)
        map->floor_color = rgb_to_int(line + 2);
    else if (strncmp(line, "C ", 2) == 0)
        map->ceiling_color = rgb_to_int(line + 2);
    else
        return true;
    return false;
}

static bool parse_grid(t_map *map, char **lines, int start_idx, int line_count)
{
    map->height = line_count - start_idx;
    map->grid = malloc(sizeof(char *) * map->height);
    entity_add_heap((t_entity *)map, map->grid);
    if (!map->grid)
        return false;
    int player_count = 0;
    for (int i = 0; i < map->height; i++)
    {
        char *row = lines[start_idx + i];
        int len = strlen(row);
        if (len > map->width)
            map->width = len;
        map->grid[i] = strdup(row);
        entity_add_heap((t_entity *)map, map->grid[i]);
        for (int j = 0; j < len; j++)
        {
            if (strchr("NSEW", row[j]))
            {
                map->player_x = j + 0.5f;
                map->player_y = i + 0.5f;
                map->player_angle = (row[j] == 'N') ? 90.0f : (row[j] == 'S') ? 270.0f : (row[j] == 'E') ? 0.0f : 180.0f;
                map->grid[i][j] = '0';
                player_count++;
            }
        }
    }
    return (player_count == 1);
}

static bool validate_map(t_map *map)
{
    if (!map->no_texture || !map->so_texture || !map->we_texture || !map->ea_texture ||
        map->floor_color == -1 || map->ceiling_color == -1)
        return false;
    for (int i = 0; i < map->height; i++)
    {
        if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
            return false;
    }
    for (int j = 0; j < map->width; j++)
    {
        if (map->grid[0][j] != '1' || map->grid[map->height - 1][j] != '1')
            return false;
    }
    return true;
}

static int rgb_to_int(char *rgb_str)
{
    int r = atoi(rgb_str);
    char *g_str = strchr(rgb_str, ',') + 1;
    int g = atoi(g_str);
    char *b_str = strchr(g_str, ',') + 1;
    int b = atoi(b_str);
    return (r << 16) | (g << 8) | b;
}

static void map_init(t_entity *self, void *params)
{
    t_map *map = (t_map *)self;
    t_map_params *p = (t_map_params *)params;
    if (!p || !p->map_file)
        return;
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->no_texture = NULL;
    map->so_texture = NULL;
    map->we_texture = NULL;
    map->ea_texture = NULL;
    map->floor_color = -1;
    map->ceiling_color = -1;
    map->player_x = -1;
    map->player_y = -1;
    map->player_angle = 0;
    map->is_valid = false;

    int fd = open(p->map_file, O_RDONLY);
    if (fd < 0)
        return;
    char *line = NULL;
    char **lines = malloc(sizeof(char *) * 100);
    entity_add_heap(self, lines);
    int line_count = 0;
    while ((line = get_next_line(fd)) && line_count < 100)
    {
        lines[line_count] = line;
        entity_add_heap(self, line);
        line_count++;
    }
    close(fd);

    int i = 0;
    while (i < line_count && !parse_config_line(map, lines[i], p->mlx))
        i++;
    if (parse_grid(map, lines, i, line_count) && validate_map(map))
        map->is_valid = true;
}

static void map_update(t_entity *self)
{
    (void)self;
}

static void map_render(t_entity *self)
{
    (void)self;
}

static const t_vtable map_vtable = {
    map_init,
    map_update,
    map_render
};

t_map *map_new(const char *map_file, void *mlx)
{
    t_map_params params = {map_file, mlx};
    return (t_map *)entity_new(sizeof(t_map), &map_vtable, &params, ENTITY_BASE);
}