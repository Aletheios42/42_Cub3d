#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void init_camera(t_camera *camera) {
    camera->offset_x = WIN_WIDTH / 2;
    camera->offset_y = WIN_HEIGHT / 2;
}

void init_game(t_game *game, t_map *map, t_mlx *mlx, t_camera *camera) {
    game->map = map;
    game->mlx = mlx;
    game->camera = camera;
}

int main(int ac, char **av) {
    t_game game;
    t_map map;
    t_mlx mlx;
    t_camera camera;

    (void)ac;
    
    ft_memset(&map, 0, sizeof(t_game));
    init_game(&game, &map, &mlx, &camera);

    ft_memset(&map, 0, sizeof(t_map));
    parser(&map, av + 1);

    ft_memset(&mlx, 0, sizeof(t_mlx));
    init_mlx(&mlx);

    ft_memset(&camera, 0, sizeof(t_camera));
    init_camera(&camera);

    render(&map, &mlx, &camera);

    mlx_hook(mlx.win, 2, 1L << 0, (void *)key_press, &game);
    mlx_hook(mlx.win, 3, 1L << 1, (void *)key_release, &game);
    mlx_hook(mlx.win, 17, 0, (void *)close_window, &game);
    mlx_loop(mlx.mlx);

    return 0;
}
