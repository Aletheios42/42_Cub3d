#include "../Inc/cube.h"
#include <math.h>
#include "../minilibx-linux/mlx.h"

float corrected_distance(float x, float y, float angle, float player_angle) {
    float dist = sqrt(x*x + y*y);
    return dist * cos(angle - player_angle);
}

void draw_wall_column(t_mlx *mlx, int column, float dist, t_map *map) {
    float height;
    int wall_start;
    int wall_end;
    int y;

    height = (BLOCK_SIZE * WIN_WIDTH) / (2 * dist);
    wall_start = (WIN_HEIGHT - height) / 2;
    wall_end = wall_start + height;
    y = 0;
    // deberia gestionar no pintar el espacio del minimapa
    // if (column < MINIMAP_WIDTH)
    //     y = MINIMAP_HEIGHT + 1;
    while (y < wall_start) 
        my_pixel_put(mlx, column, y++, map->color_ceiling);
    //Aqui tengo que cargar las texturas de las paredes
    while (y < wall_end )
        my_pixel_put(mlx, column, y++, PINK);
    while (y < WIN_HEIGHT)
        my_pixel_put(mlx, column, y++, map->color_floor);
}

void draw_3d_walls(t_mlx *mlx, t_player *player, t_map *map)
{
   float pow_angle;
   float pow_angle_limit;
   int column;
   float cos_angle; 
   float sin_angle;
   float dist;

   pow_angle_limit = player->angle + HALF_FOW;
   pow_angle = player->angle - HALF_FOW;
   column = 0;
   while (pow_angle < pow_angle_limit)
   {
       // ¿Porque hay que desplazarlo?
       // Asi esta bien pero no entiendo el + HALF_BLOCK_SIZE
       player->ray_x = player->offset_x + HALF_BLOCK_SIZE;
       player->ray_y = player->offset_y + HALF_BLOCK_SIZE;
       cos_angle = cos(pow_angle);
       sin_angle = sin(pow_angle);
       while (!touch_wall(map->map, player->ray_x, player->ray_y))
       {
           player->ray_x += cos_angle;
           player->ray_y += sin_angle;
       }
       // analizar dist cuando estoy tocando pared 
       dist = corrected_distance(player->ray_x - player->offset_x,
               player->ray_y - player->offset_y, pow_angle, player->angle);
       draw_wall_column(mlx, column++, dist, map);
       pow_angle += FOW / WIN_WIDTH;
   }
}

e_exit_status render(t_map *map, t_mlx *mlx, t_player *player)
{
    move_player(player, map);
    clear_image(mlx);
    draw_3d_walls(mlx, player, map);
    draw_minimap(map, mlx, player);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return SUCCESS;
}
