#ifndef CUBE_H
#define CUBE_H

#include "structs.h"
#include "defines.h"


e_exit_code parser(t_map*, char **);
e_exit_code render(t_map *, t_mlx *, t_camera *);

// MLX.C
e_exit_code init_mlx(t_mlx *);
void my_pixel_put(t_mlx *, int, int, int);
int close_window(t_mlx *);
int handle_key_events(int keycode, void *param);

//PLAYER.C
int key_press(int keycode, void *param);
int key_release(int keycode, void *param);

#endif
