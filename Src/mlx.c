#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>


void clear_image(t_mlx *mlx) {
    int i;
    int j;

    j = -1;
    while (++j < WIN_HEIGHT) {
        i = -1;
        while (++i < WIN_WIDTH)
            my_pixel_put(mlx, i, j, 0);
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int close_window(t_mlx *mlx) {
  mlx_destroy_image(mlx->mlx, mlx->img);
  mlx_destroy_window(mlx->mlx, mlx->win);
  mlx_destroy_display(mlx->mlx);
  exit(0);
}



void my_pixel_put(t_mlx *mlx, int x, int y, int color) {
    char *dst;

    if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return ;

    dst = mlx->addr + (y * mlx->lpl + x * mlx->bpp / 8);
    *(unsigned int*)dst = color;
}


e_exit_code init_mlx(t_mlx *mlx) {
  mlx->mlx = mlx_init();
  mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
  mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
  mlx->addr =
      mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->lpl), &(mlx->endian));

  if (!mlx->mlx || !mlx->win || !mlx->img || !mlx->addr)
      return ERR_MLX_INIT;
  return SUCCESS;
}
