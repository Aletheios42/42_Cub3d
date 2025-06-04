#ifndef STRUCTS_H
#define STRUCTS_H



typedef enum e_exit_code {
    SUCCESS,
    ERR_PASER,
    ERR_MLX_INIT,
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
    int offset_x;
    int offset_y;

    bool key_up;
    bool key_down;
    bool key_right;
    bool key_left;

    int alpha;
} t_camera;

typedef enum e_orientation {
    NO, ES, WE, SO
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
