#include "../Inc/cube.h"
int key_press(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;

    if (keycode == KEY_ESC)
        close_window(&(game->mlx));
    else if (keycode == KEY_A)
        game->player.key_left = 1;
    else if (keycode == KEY_D)
        game->player.key_right = 1;
    else if (keycode == KEY_W)
        game->player.key_up = 1;
    else if (keycode == KEY_S)
        game->player.key_down = 1;
    else if (keycode == KEY_LEFT)
        game->player.rotate_left = 1;
    else if (keycode == KEY_RIGHT)
        game->player.rotate_right = 1;

    render(&(game->map), &(game->mlx), &(game->player));
    return (0);
}

int key_release(int keycode, void *param) {
    t_game *game = 0x0;
    game = (t_game *)param;

    if (keycode == KEY_A)
        game->player.key_left = 0;
    else if (keycode == KEY_D)
        game->player.key_right = 0;
    else if (keycode == KEY_W)
        game->player.key_up = 0;
    else if (keycode == KEY_S)
        game->player.key_down = 0;
    else if (keycode == KEY_LEFT)
        game->player.rotate_left = 0;
    else if (keycode == KEY_RIGHT)
        game->player.rotate_right = 0;

    return (0);
}

