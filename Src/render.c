#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"


void draw_square(t_mlx *mlx, int x, int y, int color) {
    int i;
    int size;

    size = 20;

    i = -1;
    while (++i < size)
        my_pixel_put(mlx, x + i, y, color);
    i = -1;
    while (++i < size)
        my_pixel_put(mlx, x, y + i, color);
    i = -1;
    while (++i < size)
        my_pixel_put(mlx, x + size, y + i, color);
    i = -1;
    while (++i < size)
        my_pixel_put(mlx, x + i, y + size, color);

    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

e_exit_code render(t_map *map, t_mlx *mlx, t_camera *camera) {

    (void)map;
    draw_square(mlx,  camera->offset_x , camera->offset_y, 0x00FF00);
    return SUCCESS;

}
