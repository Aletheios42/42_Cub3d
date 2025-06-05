#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>


void draw_pov(t_mlx *mlx, t_camera *camera, t_map *map) {

    camera->ray_x = camera->offset_x;
    camera->ray_y = camera->offset_y;
    float cos_angle = cos(camera->angle);
    float sin_angle = sin(camera->angle);

    while (!touch_wall(map->map, camera->ray_x,camera->ray_y))
    {
        my_pixel_put(mlx, camera->ray_x, camera->ray_y, 0x0FF000);
        camera->ray_x += cos_angle;
        camera->ray_y += sin_angle;
    }
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

    move_player(camera);
    clear_image(mlx);
    draw_map(mlx,  map->map);
    draw_square(mlx,  camera->offset_x , camera->offset_y, 0x00FF00);
    draw_pov(mlx, camera, map);

    return SUCCESS;

}
