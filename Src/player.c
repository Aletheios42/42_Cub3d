#include "../Inc/cube.h"
#include <math.h>
#include <stdio.h>

int touch_wall(char ** map, float px, float py) {
    int x = (px / BLOCK_SIZE);
    int y = (py / BLOCK_SIZE);

    if (map[y][x] == '1')
        return 1;
    return 0;
}

// 1.revisar los if para ver si se puede mover en diagonal
// 2.revisar poner aqui un touch wall porque da segfault si me muevo fuera del mapa
// Es decir, encerrar al player
void move_player(t_player *player) {
    int offset_speed;
    float angle_speed;

    offset_speed = 5;
    angle_speed = 0.1;

    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    // printf("angle: %f cos: %f  sin: %f \n ", player->angle, cos_angle, sin_angle);

    if (player->rotate_left)
        player->angle -= angle_speed;
    if (player->rotate_right)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up) {
        player->offset_x += cos_angle * offset_speed;
        player->offset_y += sin_angle * offset_speed;
    }
    else if (player->key_down) {
        player->offset_x -= cos_angle * offset_speed;
        player->offset_y -= sin_angle * offset_speed;
    }
    else if (player->key_left) {
        player->offset_x += cos_angle * offset_speed;
        player->offset_y -= sin_angle * offset_speed;
    }
    else if (player->key_right) {
        player->offset_x -= cos_angle * offset_speed;
        player->offset_y += sin_angle * offset_speed;
    }
}
