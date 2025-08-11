#ifndef CUBE_H
#define CUBE_H

#include "structs.h"
#include "defines.h"

// PARSER_C
e_exit_status parser(t_map*, char *);

// INIT_C
void init_scene(t_scene *scene,t_map *map);

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
int parse_rgb_to_int(char *rgb_str);

// VALIDATE_MAP_C
e_exit_status validate_map(t_map *);

//FREE_C
void free_map(t_map *);

// MLX_C
e_exit_status init_mlx(t_mlx *);
void my_pixel_put(t_mlx *, int, int, int);
void clear_image(t_mlx *);
int close_window(t_mlx *);

// MINIMAP_C
// void draw_pov(t_mlx *, t_player *, t_map *);
// void draw_minimap(t_map *map, t_mlx *mlx,  t_player *player);

//HOOKS_C
int key_press(int , void *);
int key_release(int , void *);

//PLAYER_C
void move_camera(t_scene *scene, t_map *map);

//RENDER_C
int             touch_wall(char **, float , float);
e_exit_status   render(t_map *, t_mlx *, t_scene *);

//PRINT_C
void    print_map(t_map map);
void    print_mlx(t_mlx mlx);
void    print_scene(t_scene scene);
void    print_dda(t_dda dda);

#endif
