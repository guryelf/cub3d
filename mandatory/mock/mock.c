// #include "../inc/cub3d.h"
// #include "../lib/minilibx-linux/mlx.h"
// #include <stdlib.h> 
// #include <unistd.h>
// #include <stdio.h>
// #include <math.h>  
// static void generate_dummy_texture_X(t_game *game, t_img *tex)
// {
//     tex->width = 64;
//     tex->height = 64;
//     tex->img = mlx_new_image(game->mlx, 64, 64);
//
//     // Koruma eklemek her zaman iyidir
//     if (!tex->img)
//         return ;
//
//     tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
//
//     for (int y = 0; y < 64; y++)
//     {
//         for (int x = 0; x < 64; x++)
//         {
//             // XOR deseni
//             int color = ((x ^ y) & 32) ? 0x00FF0000 : 0x000000FF;
//             tex->addr[y * 64 + x] = color;
//         }
//     }
// }
//
// static void init_mock_map(t_game *game)
// {
//     game->map.width = 10;
//     game->map.height = 10;
//
//     game->map.grid = (char **)malloc(sizeof(char *) * 10);
//
//     char *template_map[] = {
//         "1111111111",
//         "1000000001",
//         "1000000001",
//         "1000110001", // Ortada bir sütun
//         "1000000001",
//         "1000000001",
//         "1000000001",
//         "10000N0001",
//         "1000000001",
//         "1111111111"
//     };
//
//     for (int i = 0; i < 10; i++)
//     {
//         game->map.grid[i] = (char *)malloc(11 *(sizeof(char))); 
//         for(int j=0; j<10; j++)
//             game->map.grid[i][j] = template_map[i][j];
//         game->map.grid[i][1] = '\0';
//     }
//
//     game->map.floor_color = 0x00333333;   // Koyu Gri
//     game->map.ceiling_color = 0x0087CEEB; // Gökyüzü Mavisi
// }
//
// // Oyuncu verilerini ayarlar
// static void init_mock_player(t_game *game)
// {
//     game->player.pos_x = 5.5; 
//     game->player.pos_y = 5.5;
//
//     game->player.dir_x = 0;
//     game->player.dir_y = -1;
//
//     game->player.plane_x = 0.66;
//     game->player.plane_y = 0;
// }
//
// void init_mlx_things(t_game *game)
// {
// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, 1920, 1080, "DUBBED");
// }
//
// void init_first_frame(t_game *game)
// {
//     game->img.img = mlx_new_image(game->mlx, 1920, 1080);
//     game->img.addr = (int *)mlx_get_data_addr(game->img.img, \
//         &game->img.bpp, &game->img.line_len, &game->img.endian);
// }
// void load_test_data(t_game *game)
// {
//     init_mlx_things(game);
//     init_mock_map(game);
//     init_mock_player(game);
//     init_first_frame(game);
//
//     // --- DÜZELTME BURADA ---
//     // Eğer struct'ta textures bir dizi ise (t_img textures[3] gibi):
//     generate_dummy_texture_X(game, &game->textures);
// }
//
//
//
// int main(void)
// {
//     t_game  game;
//
// 	load_test_data(&game);
// 	start_the_game(&game);
//
//     return (0);
// }
//
//
//
#include "../inc/cub3d.h"
#include "../lib/minilibx-linux/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

static void generate_dummy_texture_X(t_game *game, t_img *tex)
{
    tex->width = 64;
    tex->height = 64;
    tex->img = mlx_new_image(game->mlx, 64, 64);
    
    // Koruma: Görüntü oluşturulamazsa çık
    if (!tex->img)
        return ;

    tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);

    for (int y = 0; y < 64; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            // XOR deseni
            int color = ((x ^ y) & 32) ? 0x00FF0000 : 0x000000FF;
            tex->addr[y * 64 + x] = color;
        }
    }
}

static void init_mock_map(t_game *game)
{
    game->map.width = 10;
    game->map.height = 10;

    game->map.grid = (char **)malloc(sizeof(char *) * 10);

    // 'template' C++ keyword olduğu için 'template_map' kullanıldı
    char *template_map[] = {
        "1111111111",
        "1000000001",
        "1000000001",
        "1000110001",
        "1000000001",
        "1000000001",
        "1000000001",
        "10000N0001",
        "1000000001",
        "1111111111"
    };

    for (int i = 0; i < 10; i++)
    {
        // 10 karakter + 1 null terminator = 11 byte
        game->map.grid[i] = (char *)malloc(11 * (sizeof(char))); 
        for(int j = 0; j < 10; j++)
            game->map.grid[i][j] = template_map[i][j];
        
        // DÜZELTME: Satırın sonunu doğru yere koyduk (1. değil 10. indeks)
        game->map.grid[i][10] = '\0';
    }

    game->map.floor_color = 0x00333333;   // Koyu Gri
    game->map.ceiling_color = 0x0087CEEB; // Gökyüzü Mavisi
}

// Oyuncu verilerini ayarlar
static void init_mock_player(t_game *game)
{
    game->player.pos_x = 5.5; 
    game->player.pos_y = 5.5;

    game->player.dir_x = 0;
    game->player.dir_y = -1;

    game->player.plane_x = 0.66;
    game->player.plane_y = 0;
}

void init_mlx_things(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 1920, 1080, "DUBBED");
}

void init_first_frame(t_game *game)
{
    game->img.img = mlx_new_image(game->mlx, 1920, 1080);
    game->img.addr = (int *)mlx_get_data_addr(game->img.img, \
        &game->img.bpp, &game->img.line_len, &game->img.endian);
}

void load_test_data(t_game *game)
{
    init_mlx_things(game);
    init_mock_map(game);
    init_mock_player(game);
    init_first_frame(game);

    // DÜZELTME: Textures bir dizi ise ilk elemanın adresini gönderiyoruz.
    // Eğer 'textures' struct içinde bir pointer veya dizi ise bu kullanım güvenlidir.
    generate_dummy_texture_X(game, &game->textures[0]);
}


int start_the_game(t_game *game)
{
	
}

int main(void)
{
    t_game  game;

    load_test_data(&game);
    int allret = start_the_game(&game);
	if (allret != 0)
	{
		//clear
	}
    return (0);
}
