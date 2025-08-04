#include "../Inc/cube.h"
#include <math.h>

int touch_wall(char ** map, float px, float py) {
    int x = (px / BLOCK_SIZE);
    int y = (py / BLOCK_SIZE);

    if (map[y][x] == '1')
        return 1;
    return 0;
}

void handle_rotation(t_player *player) {
   float angle_speed = 0.1;
   
   if (player->rotate_left)
       player->angle -= angle_speed;
   if (player->rotate_right)
       player->angle += angle_speed;
   if (player->angle > 2 * PI)
       player->angle = 0;
   if (player->angle < 0)
       player->angle = 2 * PI;
}

void handle_movement(t_player *player, t_map *map) {
   int offset_speed = 5;
   float cos_angle = cos(player->angle);
   float sin_angle = sin(player->angle);
   float new_x = player->offset_x;
   float new_y = player->offset_y;
   
   if (player->key_up) {
       new_x += cos_angle * offset_speed;
       new_y += sin_angle * offset_speed;
   }
   else if (player->key_down) {
       new_x -= cos_angle * offset_speed;
       new_y -= sin_angle * offset_speed;
   }
   else if (player->key_left) {
       new_x += cos_angle * offset_speed;
       new_y -= sin_angle * offset_speed;
   }
   else if (player->key_right) {
       new_x -= cos_angle * offset_speed;
       new_y += sin_angle * offset_speed;
   }
   
   if (!touch_wall(map->map, new_x + 
               (float)BLOCK_SIZE/2, new_y 
               + (float)BLOCK_SIZE/2)) {
       player->offset_x = new_x;
       player->offset_y = new_y;
   }
}

void move_player(t_player *player, t_map *map) {
   handle_rotation(player);
   handle_movement(player, map);
}
