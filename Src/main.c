#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

int main(int ac, char **av) {
    t_game game;
    e_exit_status status;

    if (ac != 2)
        return printf("Error: usage: ./cube Map file\n"), 0;
    ft_memset(&game, 0, sizeof(t_game));

    status = parser(&(game.map), av[1]);
    printf("status: %d\n", status);
    if (SUCCESS != status) {
        free_map(&(game.map));
        printf("Fallo el parser\n");
        return status;
    }
    print_map(game.map);
    init_mlx(&(game.mlx));
    init_scene(&(game.scene),&(game.map));
    print_scene(game.scene);

    render(&(game.map), &(game.mlx), &(game.scene));
    mlx_hook(game.mlx.win, 2, 1L << 0, (void *)key_press, &game);
    mlx_hook(game.mlx.win, 3, 1L << 1, (void *)key_release, &game);
    mlx_hook(game.mlx.win, 17, 0, (void *)close_window, &game);
    mlx_loop(game.mlx.mlx);
    free_map(&(game.map));

    return status;
}
