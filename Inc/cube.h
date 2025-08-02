#ifndef CUBE_H
#define CUBE_H

#include "structs.h"
#include "defines.h"

// PARSER_C
e_exit_status parser(t_map*, char *);

// HANDLE_C
e_exit_status handler_texture(char *, t_map *, t_mealy *);
e_exit_status handler_color(char *, t_map *, t_mealy *);
e_exit_status handler_mapline(char *, t_map *, t_mealy *);
e_exit_status handler_empty(char *, t_map *, t_mealy *);
e_exit_status handler_error(char *, t_map *, t_mealy *);
e_exit_status handler_eof(char *, t_map *, t_mealy *);

// HANDLE_UTILS_C
e_exit_status valid_texture(char *);
e_exit_status valid_rgb(char *);
e_exit_status valid_mapline(char *, t_map *, t_mealy *, int *);

// VALIDATE_MAP_C
e_exit_status validate_map(t_map *);

//FREE_C
void free_map(t_map *);

// MLX_C
e_exit_status init_mlx(t_mlx *);
void my_pixel_put(t_mlx *, int, int, int);
void clear_image(t_mlx *);
int close_window(t_mlx *);

//HOOKS_C
int key_press(int , void *);
int key_release(int , void *);

//PLAYER_C
void move_player(t_camera *);

//RENDER_C
void draw_pov(t_mlx *, t_camera *, t_map *);
int touch_wall(char **, float, float);
e_exit_status render(t_map *, t_mlx *, t_camera *);

//PRINT_C
void  print_map(t_map map);

#endif
