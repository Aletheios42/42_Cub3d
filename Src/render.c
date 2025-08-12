#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <sys/time.h>

char *get_fps(struct timeval frame_start) {
    static char buf[16];
    struct timeval frame_end;
    double elapsed, fps;

    gettimeofday(&frame_end, NULL);

    elapsed = (frame_end.tv_sec - frame_start.tv_sec)
            + (frame_end.tv_usec - frame_start.tv_usec) / 1e6;

    fps = (elapsed > 0.0) ? (1.0 / elapsed) : 0.0;

    intToStr((int)fps, buf);
    return buf;
}

void perform_raycasting(t_map *map, t_mlx *mlx, t_scene *scene) {
    int col;
    t_dda dda;

    col = -1;
     while (++col < WIN_WIDTH) {
        init_ray(&dda, &scene->camera, col);
        calculate_step_and_sidedist(&dda, &scene->camera);
        perform_dda(&dda, map);
        calculate_wall_distance(&dda);
        draw_wall_stripe(mlx, &dda, col, map);
    }
}

static void draw_controls_help(t_mlx *mlx)
{
    mlx_string_put(mlx->mlx, mlx->win, 20, 40, MENU_COLOR_STR, "W: Move forward");
    mlx_string_put(mlx->mlx, mlx->win, 20, 60, MENU_COLOR_STR, "S: Move backward");
    mlx_string_put(mlx->mlx, mlx->win, 20, 80, MENU_COLOR_STR, "A: Move left");
    mlx_string_put(mlx->mlx, mlx->win, 20,100, MENU_COLOR_STR, "D: Move right");
    mlx_string_put(mlx->mlx, mlx->win, 20,120, MENU_COLOR_STR, "Left/Right: Rotate");
    mlx_string_put(mlx->mlx, mlx->win, 20,140, MENU_COLOR_STR, "M: Toggle menu");
    mlx_string_put(mlx->mlx, mlx->win, 20,160, MENU_COLOR_STR, "+/-: Change speed");
}

void set_menu(t_mlx *mlx, t_controls *controls, t_params *params, t_camera *camera)
{
    int y;
    int x;

    (void)controls;
    (void)params;
    (void)camera;
    y = -1;
    while (++y < WIN_HEIGHT)
    {
        x = -1;
        while (++x < MENU_WIDTH)
            my_pixel_put(mlx, x, y, MENU_COLOR);
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    draw_controls_help(mlx);
}

//pensar como hago el menu, con sin minimap, ocupando todo,
//sobre el mapa renderizado o yo que coño se ajajjaja
e_exit_status render(t_map *map, t_mlx *mlx, t_scene *scene) {
    struct timeval frame_start;

    gettimeofday(&frame_start, NULL);
    clear_image(mlx);
    if (scene->controls.menu) {
        set_menu(mlx, &scene->controls, &scene->params, &scene->camera);
        // draw_minimap(map, mlx, scene);
    }
    else {
        move_player(scene, map);
        perform_raycasting(map, mlx, scene);
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    }
    //repensar donde poner el marcador de los fps
    mlx_string_put(mlx->mlx, mlx->win, WIN_HEIGHT - 100, WIN_WIDTH - 100, RED, get_fps(frame_start));
    return SUCCESS;
}
