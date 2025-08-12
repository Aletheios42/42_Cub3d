
#include "../Inc/cube.h"
#include <math.h>
// void draw_line(t_mlx *mlx, t_player player, t_map *map, float pow_angle) {
//         float cos_angle;
//         float sin_angle;
//
//         cos_angle = cos(pow_angle);
//         sin_angle= sin(pow_angle);
//         while (!touch_wall(map->map, player.ray_x, player.ray_y))
//         {
//             my_pixel_put(mlx, player.ray_x, player.ray_y, BLUE);
//             player.ray_x += cos_angle;
//             player.ray_y += sin_angle;
//         }
// }
//
// //El BLOCK TIENE QUE SER PROPIO
// void draw_pov(t_mlx *mlx, t_player *player, t_map *map) {
//     float pow_angle;
//     float pow_angle_limit;
//
//     pow_angle = player->angle - HALF_FOW;
//     pow_angle_limit = player->angle + HALF_FOW;
//     player->ray_x = player->offset_x;
//     player->ray_y = player->offset_y;
//     while (pow_angle < pow_angle_limit) {
//         draw_line(mlx, *player, map, pow_angle);
//         pow_angle += FOW / WIN_WIDTH;
//     }
// }
//
// //El BLOCK TIENE QUE SER PROPIO
// void draw_square(t_mlx *mlx, int x, int y, int color) {
//     int i;
//
//     my_pixel_put(mlx, x, y, color);
//     i = -1;
//     while (++i < BLOCK_SIZE)
//         my_pixel_put(mlx, x + i  - HALF_BLOCK_SIZE, y  - HALF_BLOCK_SIZE, color);
//     i = -1;
//     while (++i < BLOCK_SIZE)
//         my_pixel_put(mlx, x - HALF_BLOCK_SIZE, y + i - HALF_BLOCK_SIZE, color);
//     i = -1;
//     while (++i < BLOCK_SIZE)
//         my_pixel_put(mlx, x + HALF_BLOCK_SIZE, y + i - HALF_BLOCK_SIZE, color);
//     i = -1;
//     while (++i < BLOCK_SIZE)
//         my_pixel_put(mlx, x + i - HALF_BLOCK_SIZE, y + HALF_BLOCK_SIZE, color);
// }
//
// //El BLOCK TIENE QUE SER PROPIO
// void draw_squared_map(t_mlx *mlx, char **map) {
//     int i;
//     int j;
//
//     i = -1;
//     while (map[++i]) {
//         j = -1;
//         while (map[i][++j]) {
//             if (map[i][j] == '1')
//                 draw_square(mlx, j * BLOCK_SIZE, i * BLOCK_SIZE, RED);
//         }
//     }
// }
//
//
// void draw_minimap(t_map *map, t_mlx *mlx,  t_player *player)
// {
//     draw_squared_map(mlx, map->map);
//     //Tengo que pensar que la posicion del player 
//     //en el mapa3D y en el minimapa , estan relacionadas 
//     //pero no son iguales
//     draw_square(mlx, player->offset_x, player->offset_y, GREEN);
//     draw_pov(mlx, player, map);
// }
