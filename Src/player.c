#include "../Inc/cube.h"
#include <math.h>

// hay que caracteriza las caras, no es lo mismo
// chocar ocn una cara N que con una S
int touch_wall(char ** map, float px, float py) {
    int x;
    int y;

    // el angulo de player importa
    x = (px / BLOCK_SIZE);
    y = (py / BLOCK_SIZE);

    if (map[y][x] == '1')
        return 1;
    return 0;
}

void init_player(t_player *player, t_map *map)
{
    // ¿¿Por que HALF_BLOCK_SIZE y no HITBOX??
    player->offset_x = (map->player_pos[0] * BLOCK_SIZE);
    player->offset_y = (map->player_pos[1] * BLOCK_SIZE);
    player->offset_speed = 3;
    player->angle_speed = 0.1;

    if ('N' == map->orientation)
        player->angle = 3 * PI / 2;
    else if ('S' == map->orientation)
        player->angle = PI / 2;
    else if ('E' == map->orientation)
        player->angle = 0;
    else if ('W' == map->orientation)
        player->angle = PI;
}

void handle_rotation(t_player *player) {
   
   if (player->rotate_left)
       player->angle -= player->angle_speed;
   if (player->rotate_right)
       player->angle += player->angle_speed;
   if (player->angle > 2 * PI)
       player->angle = 0;
   if (player->angle < 0)
       player->angle = 2 * PI;
}

void handle_movement(t_player *player, t_map *map) {
    float cos_angle;
    float sin_angle;
    float new_x;
    float new_y;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    new_x = player->offset_x;
    new_y = player->offset_y;
    new_x += player->offset_speed * ( cos_angle * (player->key_up - player->key_down)
                    + sin_angle * (player->key_right - player->key_left));
    new_y += player->offset_speed * ( sin_angle * (player->key_up - player->key_down)
                    + cos_angle * (player->key_left - player->key_right));
    //¿Replantear HITBOX, no digo que esta mal solo que no lo entiendo
    // if (!touch_wall(map->map, new_x + HITBOX, new_y + HITBOX)
    //         && !touch_wall(map->map, new_x + HITBOX, new_y - HITBOX)
    //         && !touch_wall(map->map, new_x - HITBOX, new_y + HITBOX)
    //         && !touch_wall(map->map, new_x - HITBOX, new_y - HITBOX)
    //     )
    if (!touch_wall(map->map, new_x, new_y))
    {
        player->offset_x = new_x;
        player->offset_y = new_y;
        player->ray_x = player->offset_x;
        player->ray_y = player->offset_y;
    }
    printf("x: %f, y: %f\n", player->offset_x, player->offset_y);
}

void move_player(t_player *player, t_map *map) {
   handle_rotation(player);
   handle_movement(player, map);
}
