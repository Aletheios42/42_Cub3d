#ifndef CUBE_H
#define CUBE_H

#include "structs.h"
#include "defines.h"


e_exit_code parser(t_map*, char **);

// MLX_C
e_exit_code init_mlx(t_mlx *);
void my_pixel_put(t_mlx *, int, int, int);
void clear_image(t_mlx *);
int close_window(t_mlx *);

//HOOKS_C
int key_press(int , void *);
int key_release(int , void *);

//PLAYER_C
void move_player(t_camera *);


//RENDER_H
void draw_pov(t_mlx *, t_camera *, t_map *);
int touch_wall(char **, float, float);
e_exit_code render(t_map *, t_mlx *, t_camera *);

#endif
