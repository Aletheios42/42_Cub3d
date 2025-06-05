#ifndef CUBE_H
#define CUBE_H

#include "structs.h"
#include "defines.h"


e_exit_code parser(t_map*, char **);
e_exit_code render(t_map *, t_mlx *, t_camera *);

// MLX.C
e_exit_code init_mlx(t_mlx *);
void my_pixel_put(t_mlx *, int, int, int);
void clear_image(t_mlx *mlx);
int close_window(t_mlx *);

//PLAYER.C
int key_press(int , void *);
int key_release(int , void *);
void move_player(t_camera *);

#endif
