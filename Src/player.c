#include "../Inc/cube.h"


int key_press(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;

    if (keycode == KEY_ESC)
        close_window(game->mlx);

    else if (keycode == KEY_A)
        game->camera->key_left = 1;
    else if (keycode == KEY_D)
        game->camera->key_right = 1;
    else if (keycode == KEY_W)
        game->camera->key_up = 1;
    else if (keycode == KEY_S)
        game->camera->key_down = 1;

    render(game->map, game->mlx, game->camera);
    return (0);
}

int key_release(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;


    if (keycode == KEY_A)
        game->camera->key_left = 0;
    else if (keycode == KEY_D)
        game->camera->key_right = 0;
    else if (keycode == KEY_W)
        game->camera->key_up = 0;
    else if (keycode == KEY_S)
        game->camera->key_down = 0;

    return (0);
}

void move_player(t_camera *camera) {
    int speed;

    speed = 5;
    if (camera->key_up)
        camera->offset_y -= speed;
    else if (camera->key_down)
        camera->offset_y += speed;
    else if (camera->key_left)
        camera->offset_x -= speed;
    else if (camera->key_right)
        camera->offset_x += speed;

}
