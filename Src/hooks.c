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
    else if (keycode == KEY_M)
        game->scene.controls.menu ^= 1;

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


//Repensar esta funcion, pretende modificar los valores de t_params
// creo que es mejor un sistema del tipo:
// Pulsa 1,2,3 para editar traslation, rotation, fow
// y una vez selcionado + y -
// int key_press_params(int keycode, t_game *game)
// {
//     t_params *p;
//
//     p = &game->scene.params;
//     if (keycode == KEY_PLUS)
//         p->rotation_speed += 0.05;
//     else if (keycode == KEY_MINUS && p->rotation_speed > 0.05)
//         p->rotation_speed -= 0.05;
//     else if (keycode == KEY_RIGHT_BRACKET)
//         p->trasnlation_speed += 0.1f;
//     else if (keycode == KEY_LEFT_BRACKET && p->trasnlation_speed > 0.1f)
//         p->trasnlation_speed -= 0.1f;
//     else if (keycode == KEY_CURLY_CLOSE) /* '}' */
//         p->fieldOfView += PI / 180.0 * 5; /* +5 degrees */
//     else if (keycode == KEY_CURLY_OPEN && p->fieldOfView > PI / 180.0 * 10)
//         p->fieldOfView -= PI / 180.0 * 5; /* -5 degrees */
//     else if (keycode == KEY_PERIOD)
//         p->block_size += 1;
//     else if (keycode == KEY_COMMA && p->block_size > 1)
//         p->block_size -= 1;
//     return (0);
// }
