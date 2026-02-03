
typedef struct s_img
{
    void    *img;
    int     *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_map
{
    char    **grid;         // Harita matrisi (1, 0, N, S...)
    int     width;
    int     height;
    char    *no_path;       // Texture yolları
    char    *so_path;
    // ... diğer pathler ve floor/ceiling renkleri (int color)
}   t_map;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;          // Bakış yönü vektörü
    double  dir_y;
    double  plane_x;        // Kamera düzlemi (FOV için)
    double  plane_y;
}   t_player;

typedef struct s_ray
{
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;            // Duvara çarptı mı?
    int     side;           // NS (0) mi EW (1) mi?
    int     line_height;
}   t_ray;

// ANA STRUCT: Fonksiyonlara sadece bunu göndereceksiniz!
typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       img;        // Ekran Buffer'ı
    t_map       map;        // Harita verileri
    t_player    player;     // Oyuncu verileri
    t_ray       ray;        // Raycasting değişkenleri
    t_img       textures[1]; // 4 Duvar texture'ı
}   t_game;

