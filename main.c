#include "scene.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    t_scene *scene = scene_new(argv[1]);
    if (!scene)
        return 1;
    game_run(scene);
    return 0;
}