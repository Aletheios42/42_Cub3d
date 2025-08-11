#include "../Inc/cube.h"
int key_press(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;

    if (keycode == KEY_ESC)
        return close_window(&(game->mlx));
    else if (keycode == KEY_A)
        game->scene.controls.key_left = 1;
    else if (keycode == KEY_D)
        game->scene.controls.key_right = 1;
    else if (keycode == KEY_W)
        game->scene.controls.key_up = 1;
    else if (keycode == KEY_S)
        game->scene.controls.key_down = 1;
    else if (keycode == KEY_LEFT)
        game->scene.controls.rotate_left = 1;
    else if (keycode == KEY_RIGHT)
        game->scene.controls.rotate_right = 1;

    render(&(game->map), &(game->mlx), &(game->scene));
    return (0);
}

int key_release(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;

    if (keycode == KEY_A)
        game->scene.controls.key_left = 0;
    else if (keycode == KEY_D)
        game->scene.controls.key_right = 0;
    else if (keycode == KEY_W)
        game->scene.controls.key_up = 0;
    else if (keycode == KEY_S)
        game->scene.controls.key_down = 0;
    else if (keycode == KEY_LEFT)
        game->scene.controls.rotate_left = 0;
    else if (keycode == KEY_RIGHT)
        game->scene.controls.rotate_right = 0;

    return (0);
}

