#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void init_player(t_player *player, t_map map) {
    player->offset_x = map.player_pos[0] * BLOCK_SIZE + (BLOCK_SIZE /2.0f);
    player->offset_y = map.player_pos[1] * BLOCK_SIZE + (BLOCK_SIZE /2.0f);

    // Establecer ángulo inicial según orientación del mapa
    switch (map.orientation) {
        case N:
            player->angle = 3 * PI / 2;  // 270 grados
            break;
        case S:
            player->angle = PI / 2;      // 90 grados
            break;
        case E:
            player->angle = 0;           // 0 grados
            break;
        case W:
            player->angle = PI;          // 180 grados
            break;
    }
    
}

int main(int ac, char **av) {
    t_game game;
    e_exit_status status;

    if (ac != 2)
        return 0;
    ft_memset(&game, 0, sizeof(t_game));

    status = parser(&(game.map), av[1]);
    //   DEBUG
    printf("\n====================\n");
    printf("Status del parser: %d\n", status);
    print_map(game.map);
    if (SUCCESS != status) {
        free_map(&(game.map));
        printf("Fallo el parser\n");
        return status;
    }

    init_mlx(&(game.mlx));
    init_player(&(game.player), game.map);

    render(&(game.map), &(game.mlx), &(game.player));

    mlx_hook(game.mlx.win, 2, 1L << 0, (void *)key_press, &game);
    mlx_hook(game.mlx.win, 3, 1L << 1, (void *)key_release, &game);
    mlx_hook(game.mlx.win, 17, 0, (void *)close_window, &game);
    mlx_loop(game.mlx.mlx);

    free_map(&(game.map));
    return status;
}
