#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void init_player(t_player *player, t_map map) {
    player->offset_x = map.player_pos[0] * BLOCK_SIZE + HALF_BLOCK_SIZE;
    player->offset_y = map.player_pos[1] * BLOCK_SIZE + HALF_BLOCK_SIZE;
    
    if (N == map.orientation)
        player->angle = 3 * PI / 2;
    else if (S == map.orientation)
        player->angle = PI / 2;
    else if (E == map.orientation)
        player->angle = 0;
    else if (W == map.orientation)
        player->angle = PI;
}

int main(int ac, char **av) {
    t_game game;
    e_exit_status status;

    if (ac != 2)
        return 0;
    ft_memset(&game, 0, sizeof(t_game));

    status = parser(&(game.map), av[1]);
    init_mlx(&(game.mlx));
    init_player(&(game.player), game.map);

    if (SUCCESS != status) {
        free_map(&(game.map));
        printf("Fallo el parser\n");
        return status;
    }
    //   DEBUG
    if (DEBUG) {
        print_map(game.map);
        print_player(game.player);
        print_mlx(game.mlx);
    }

    render(&(game.map), &(game.mlx), &(game.player));

    mlx_hook(game.mlx.win, 2, 1L << 0, (void *)key_press, &game);
    mlx_hook(game.mlx.win, 3, 1L << 1, (void *)key_release, &game);
    mlx_hook(game.mlx.win, 17, 0, (void *)close_window, &game);
    mlx_loop(game.mlx.mlx);

    free_map(&(game.map));
    return status;
}
