#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void init_camera(t_camera *camera) {
    camera->offset_x = WIN_WIDTH / 2;
    camera->offset_y = WIN_HEIGHT / 2;
}

int main(int ac, char **av) {
    t_game game;
    e_exit_status status;

    if (ac != 2)
        return 0;
    ft_memset(&game, 0, sizeof(t_game));

    status = parser(&(game.map), av[1]);
    // DEBUG
    // printf("status del parser: %d\n", status);
    // print_map(game.map);
    if (SUCCESS != status) {
        free_map(&(game.map));
        printf("Fallo el parser\n");
        return status;
    }

    init_mlx(&(game.mlx));

    // init_camera(&(game.camera));

    // render(&(game.map), &(game.mlx), &(game.camera));
    //
    // mlx_hook(game.mlx.win, 2, 1L << 0, (void *)key_press, &game);
    // mlx_hook(game.mlx.win, 3, 1L << 1, (void *)key_release, &game);
    // mlx_hook(game.mlx.win, 17, 0, (void *)close_window, &game);
    // mlx_loop(game.mlx.mlx);

    free_map(&(game.map));
    return status;
}
