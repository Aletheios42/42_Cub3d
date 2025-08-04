#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdio.h>

typedef enum e_exit_status {
    SUCCESS,
    ERR_PARSER,
    ERR_INVALID_LINE,
    ERR_INVALID_MAP,
    ERR_OPEN,
    ERR_MLX_INIT,
    ERR_FAIL_MALLOC,
    ERR_INVALIAD_ROUTE_MAP,
    ERR_DUPLICATED_FIELD,
    ERR_BAD_EXTENSION,
    ERR_INVALID_TEXTURE,
    ERR_INVALID_COLOR_FORMAT,
    ERR_INVALID_COLOR_RANGE,
    ERR_INVALID_MAP_CHAR,
    ERR_DUPLICATED_PLAYER,
} e_exit_status;

typedef enum e_state {
    STATE_START,
    STATE_HEADER,
    STATE_MAP,
    STATE_ERR,
    STATE_END,
    STATE_COUNT
} t_state;

typedef enum e_event {
    EVENT_TEX_NO,
    EVENT_TEX_SO,
    EVENT_TEX_WE,
    EVENT_TEX_EA,
    EVENT_COL_C,
    EVENT_COL_F,
    EVENT_MAP_LINE,
    EVENT_EMPTY,
    EVENT_INVALID,
    EVENT_EOF,
    EVENT_COUNT
} t_event;

typedef struct s_mealy t_mealy;

typedef struct s_map t_map;
typedef e_exit_status (*t_handler)(char *line, t_map *map, t_mealy *machine);

typedef struct s_mealy {
    t_state (*transitions)[EVENT_COUNT];
    t_handler (*outputs)[EVENT_COUNT];
    t_state current_state;
    t_event current_event;
    uint8_t tokens_mask;
} t_mealy;

typedef enum e_orientation {
    N, E, W, S
} e_orientation;

typedef struct s_map {
    char **map;
    char *texture_no;
    char *texture_so;
    char *texture_we;
    char *texture_ea;
    char *color_floor;
    char *color_celing;
    e_orientation orientation;
    int player_pos[2];
    int height;
    int *width; //hacerla puntero para evitar mapas cuadrados
} t_map;

typedef struct s_mlx {
    void*   mlx;
    void*   win;
    void*   img;
    void*   addr;
    int     bpp;
    int     lpl;
    int     endian;
} t_mlx;

typedef struct s_player {
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
} t_player;



typedef struct s_game {
    t_map map;
    t_mlx mlx;
    t_player player;
} t_game;

#endif
