#include "../Inc/cube.h"
#include <math.h>
#include "../minilibx-linux/mlx.h"

void init_ray(t_dda *dda, t_camera *camera, int col) {
    double cameraX;

    cameraX = 2.0 * col / (double)WIN_WIDTH - 1.0;
    dda->rayDir_x = camera->dir_x + camera->plane_x * cameraX;
    dda->rayDir_y = camera->dir_y + camera->plane_y * cameraX;
    dda->map_x = (int)camera->pos_x;
    dda->map_y = (int)camera->pos_y;
    dda->deltaDist_x = (dda->rayDir_x == 0) ? 1e30 : fabs(1.0 / dda->rayDir_x);
    dda->deltaDist_y = (dda->rayDir_y == 0) ? 1e30 : fabs(1.0 / dda->rayDir_y);
    dda->hit = 0;
    dda->side = 0;
}

void calculate_step_and_sidedist(t_dda *dda, t_camera *camera) {
    if (dda->rayDir_x < 0) {
        dda->step_x = -1;
        dda->sideDist_x = (camera->pos_x - (double)dda->map_x) * dda->deltaDist_x;
    } else {
        dda->step_x = 1;
        dda->sideDist_x = ((double)dda->map_x + 1.0 - camera->pos_x) * dda->deltaDist_x;
    }
    if (dda->rayDir_y < 0) {
        dda->step_y = -1;
        dda->sideDist_y = (camera->pos_y - (double)dda->map_y) * dda->deltaDist_y;
    } else {
        dda->step_y = 1;
        dda->sideDist_y = ((double)dda->map_y + 1.0 - camera->pos_y) * dda->deltaDist_y;
    }
}

void perform_dda(t_dda *dda, t_map *map) {
    while (!dda->hit) {
        // Jump to next map square, either in x-direction, or in y-direction
        if (dda->sideDist_x < dda->sideDist_y) {
            dda->sideDist_x += dda->deltaDist_x;
            dda->map_x += dda->step_x;
            dda->side = 0;
        } else {
            dda->sideDist_y += dda->deltaDist_y;
            dda->map_y += dda->step_y;
            dda->side = 1;
        }
        if (dda->map_x < 0 || dda->map_x >= map->width || 
            dda->map_y < 0 || dda->map_y >= map->height) {
            dda->hit = 1;
            break;
        }
        if (map->map[dda->map_y][dda->map_x] != '0') {
            dda->hit = 1;
        }
    }
}

void calculate_wall_distance(t_dda *dda) {
    if (dda->side == 0) {
        dda->wallDist = (dda->sideDist_x - dda->deltaDist_x);
    } else {
        dda->wallDist = (dda->sideDist_y - dda->deltaDist_y);
    }
}

void draw_wall_stripe(t_mlx *mlx, t_dda *dda, int col, t_map *map) {
    double perpWallDist;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;
    int y;

    perpWallDist = dda->wallDist;
    
    if (perpWallDist <= 0.0001) {
        perpWallDist = 0.0001;
    }
    
    lineHeight = (int)(WIN_HEIGHT / perpWallDist);
    drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
    if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;
    
    if (dda->side == 1) {
        color = 0x808080;
    } else {
        color = 0xFFFFFF;
    }
    y = 0;
    while (y < drawStart)
        my_pixel_put(mlx, col, y++, map->color_floor);
    //AQUI VAN LAS TEXTURAS
    while (y <= drawEnd)
        my_pixel_put(mlx, col, y++, color);
    while (y <= WIN_HEIGHT)
        my_pixel_put(mlx, col, y++, map->color_ceiling);
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

e_exit_status render(t_map *map, t_mlx *mlx, t_scene *scene) {
    move_player(scene, map);
    clear_image(mlx);
    perform_raycasting(map, mlx, scene);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return SUCCESS;
}
