#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

//no basta con t_player hay que hacer un t_scene {
// t_player
// t_minimap
// t_params
//}
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
    free_map(&(game.map));
    // init_mlx(&(game.mlx));
    // init_player(&(game.player), &(game.map));
    //
    // if (DEBUG) {
    //     print_map(game.map);
    //     print_player(game.player);
    //     print_mlx(game.mlx);
    // }
    //
    // render(&(game.map), &(game.mlx), &(game.player));
    //
    // mlx_hook(game.mlx.win, 2, 1L << 0, (void *)key_press, &game);
    // mlx_hook(game.mlx.win, 3, 1L << 1, (void *)key_release, &game);
    // mlx_hook(game.mlx.win, 17, 0, (void *)close_window, &game);
    // mlx_loop(game.mlx.mlx);
    return status;
}
