#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"


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

void draw_map(t_mlx *mlx, char **map) {

    int color;
    int i;
    int j;

    color = 0xFF0000;

    i = -1;
    while (map[++i]) {
        j = -1;
        while (map[i][++j]) {
            if (map[i][j] == '1')
                draw_square(mlx, j * BLOCK, i * BLOCK, color);
        }
    }
}

e_exit_code render(t_map *map, t_mlx *mlx, t_camera *camera) {

    (void)map;
    move_player(camera);
    clear_image(mlx);
    draw_map(mlx,  map->map);
    draw_square(mlx,  camera->offset_x , camera->offset_y, 0x00FF00);
    return SUCCESS;

}
