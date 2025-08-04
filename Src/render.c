#include "../Inc/cube.h"
#include <math.h>

float corrected_distance(float x, float y, float angle, float player_angle) {
    float dist = sqrt(x*x + y*y);
    return dist * cos(angle - player_angle);
}

void draw_wall_column(t_mlx *mlx, int column, float dist) {
    float height = (BLOCK_SIZE * WIN_WIDTH) / (2 * dist);
    int start_y = (WIN_HEIGHT - height) / 2;
    int end = start_y + height;
    
    while (start_y < end) {
        my_pixel_put(mlx, column, start_y, PINK);
        start_y++;
    }
}

void draw_3d_walls(t_mlx *mlx, t_player *player, t_map *map) {
   float pow_angle = player->angle - ((float)FOW / 2);
   float pow_angle_limit = player->angle + ((float)FOW / 2);
   int column;

   column = 0;
   while (pow_angle < pow_angle_limit) {
       player->ray_x = player->offset_x + (float)BLOCK_SIZE / 2;
       player->ray_y = player->offset_y + (float)BLOCK_SIZE / 2;
       float cos_angle = cos(pow_angle);
       float sin_angle = sin(pow_angle);
       while (!touch_wall(map->map, player->ray_x, player->ray_y)) {
           player->ray_x += cos_angle;
           player->ray_y += sin_angle;
       }
       float dist = corrected_distance(player->ray_x - player->offset_x,
               player->ray_y - player->offset_y,
               pow_angle, player->angle);
       draw_wall_column(mlx, column, dist);
       column++;
       pow_angle += PI / 3 / WIN_WIDTH;
   }
}

void draw_line(t_mlx *mlx, t_player player, t_map *map, float pow_angle) {
        float cos_angle = cos(pow_angle);
        float sin_angle = sin(pow_angle);
        while (!touch_wall(map->map, player.ray_x, player.ray_y))
        {
            my_pixel_put(mlx, player.ray_x, player.ray_y, BLUE);
            player.ray_x += cos_angle;
            player.ray_y += sin_angle;
        }
}

void draw_pov(t_mlx *mlx, t_player *player, t_map *map) {
    float pow_angle = player->angle - ((float)FOW /2);
    float pow_angle_limit = player->angle + ((float)FOW /2);
    player->ray_x = player->offset_x + (float)BLOCK_SIZE / 2;
    player->ray_y = player->offset_y + (float)BLOCK_SIZE / 2;
    while (pow_angle < pow_angle_limit) {
        draw_line(mlx, *player, map, pow_angle);
        pow_angle += PI / 3 / WIN_WIDTH;
    }
}

void draw_square(t_mlx *mlx, int x, int y, int color) {
    int i;

    i = -1;
    while (++i < BLOCK_SIZE)
        my_pixel_put(mlx, x + i, y, color);
    i = -1;
    while (++i < BLOCK_SIZE)
        my_pixel_put(mlx, x, y + i, color);
    i = -1;
    while (++i < BLOCK_SIZE)
        my_pixel_put(mlx, x + BLOCK_SIZE, y + i, color);
    i = -1;
    while (++i < BLOCK_SIZE)
        my_pixel_put(mlx, x + i, y + BLOCK_SIZE, color);

}

void draw_map(t_mlx *mlx, char **map) {
    int i;
    int j;

    i = -1;
    while (map[++i]) {
        j = -1;
        while (map[i][++j]) {
            if (map[i][j] == '1')
                draw_square(mlx, j * BLOCK_SIZE, i * BLOCK_SIZE, RED);
        }
    }
}

e_exit_status render(t_map *map, t_mlx *mlx, t_player *player) {
    move_player(player, map);
    clear_image(mlx);
    if (DEBUG) {
        draw_map(mlx, map->map);
        draw_square(mlx, player->offset_x, player->offset_y, GREEN);
        draw_pov(mlx, player, map);
    }
    else
        draw_3d_walls(mlx, player, map);
    return SUCCESS;
}
