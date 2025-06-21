#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_exit_code {
    SUCCESS,
    ERR_PASER,
    ERR_MLX_INIT,
    ERR_FAIL_MALLOC,
} e_exit_code;

typedef struct s_mlx {
    void*   mlx;
    void*   win;
    void*   img;
    void*   addr;
    int     bpp;
    int     lpl;
    int     endian;
} t_mlx;

typedef struct s_camera {
    float offset_x;
    float offset_y;

    float ray_x;
    float ray_y;

    bool key_up;
    bool key_down;
    bool key_right;
    bool key_left;
    bool rotate_right;
    bool rotate_left;

    float angle;
} t_camera;

typedef enum e_orientation {
    N, E, W, S
} e_orientation;

typedef struct s_map {
    char **map;
    e_orientation orientation;

} t_map;

typedef struct s_game {
    t_map *map;
    t_mlx *mlx;
    t_camera *camera;
} t_game;

#endif
