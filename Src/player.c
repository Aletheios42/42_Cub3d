#include "../Inc/cube.h"
#include <math.h>
#include <stdio.h>


int touch_wall(char ** map, float px, float py) {
    int x = px / BLOCK;
    int y = py / BLOCK;

    if (map[y][x] == '1')
        return 1;
    return 0;
}

// repensar los += y -= con los angulos
void move_player(t_camera *camera) {
    int offset_speed;
    float angle_speed;

    offset_speed = 5;
    angle_speed = 0.1;

    float cos_angle = cos(camera->angle);
    float sin_angle = sin(camera->angle);

    printf("angle: %f cos: %f  sin: %f \n ", camera->angle, cos_angle, sin_angle);


    if (camera->rotate_left)
        camera->angle += angle_speed;
    if (camera->rotate_right)
        camera->angle -= angle_speed;
    if (camera->angle > 2 * PI)
        camera->angle = 0;
    if (camera->angle < 0)
        camera->angle = 2 * PI;

    if (camera->key_up) {
        camera->offset_x += cos_angle * offset_speed;
        camera->offset_y += sin_angle * offset_speed;
    }
    else if (camera->key_down) {
        camera->offset_x -= cos_angle * offset_speed;
        camera->offset_y -= sin_angle * offset_speed;
    }
    else if (camera->key_left) {
        camera->offset_x += cos_angle * offset_speed;
        camera->offset_y -= sin_angle * offset_speed;
    }
    else if (camera->key_right) {
        camera->offset_x -= cos_angle * offset_speed;
        camera->offset_y += sin_angle * offset_speed;
    }
}
