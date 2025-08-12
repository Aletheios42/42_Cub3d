#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum e_exit_status {
    SUCCESS,
    ERR_PARSER,
    ERR_INVALID_LINE,
    ERR_INVALID_MAP,
    ERR_MAP_IS_NOT_CLOSE,
    ERR_OPEN,
    ERR_MLX_INIT,
    ERR_FAIL_MALLOC,
    ERR_INVALIAD_ROUTE_MAP,
    ERR_DUPLICATED_FIELD,
    ERR_BAD_EXTENSION,
    ERR_INVALID_TEXTURE,
    ERR_INVALID_COLOR_FORMAT,
    ERR_INVALID_RGB,
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

typedef struct s_map {
    char **map;
    char *texture_no;
    char *texture_so;
    char *texture_we;
    char *texture_ea;
    int color_floor;
    int color_ceiling;
    char orientation;
    int player_pos[2];
    int height;
    int width;
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

typedef struct s_camera {
   float pos_x;     // Player position X coordinate on the map
   float pos_y;     // Player position Y coordinate on the map
   float dir_x;     // Camera direction vector X component
   float dir_y;     // Camera direction vector Y component
   float plane_x;   // Camera plane vector X component (perpendicular to dir)
   float plane_y;   // Camera plane vector Y component (perpendicular to dir)
} t_camera;

typedef struct s_params {
    float rotation_speed;
    float trasnlation_speed;
    int block_size;
    float fieldOfView;
} t_params;

typedef struct s_controls {
    bool key_up;
    bool key_down;
    bool key_right;
    bool key_left;
    bool rotate_right;
    bool rotate_left;
    bool menu;
} t_controls;

typedef struct s_scene {
    t_controls controls;
    t_params params;
    t_camera camera;
} t_scene;

typedef struct s_dda {
    int map_x; // coordenada x de la celda en la que te encuentras
    int map_y; // coordenada y de la celda en la que te encuentras

    double rayDir_x; //Direccion X del rayo
    double rayDir_y; //Direccion Y del rayo

    double sideDist_x; //Distancia del rayo a la columna de la celda 
    double sideDist_y; //Distancia del rayo a la fila de la celda

    double deltaDist_x; //Distancia del rayo a la prixima columna de la rejilla
    double deltaDist_y; //Distancia del rayo a la prixima fila de la rejilla
    double wallDist; //Distancia ortogonal a la pared

    int step_x;
    int step_y;
    bool hit;
    int side;

} t_dda;

typedef struct s_game {
    t_map map;
    t_mlx mlx;
    t_scene scene;
} t_game;

#endif
