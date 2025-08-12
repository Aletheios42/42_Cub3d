#include "../Inc/cube.h"
#include <math.h>

void handle_rotation(t_scene *scene) {
    t_camera *camera = &scene->camera;
    float rot_speed = scene->params.rotation_speed;
    
    if (scene->controls.rotate_left) {
        // Rotate clockwise (negative rotation)
        float old_dir_x = camera->dir_x;
        camera->dir_x = camera->dir_x * cos(-rot_speed) - camera->dir_y * sin(-rot_speed);
        camera->dir_y = old_dir_x * sin(-rot_speed) + camera->dir_y * cos(-rot_speed);
        
        float old_plane_x = camera->plane_x;
        camera->plane_x = camera->plane_x * cos(-rot_speed) - camera->plane_y * sin(-rot_speed);
        camera->plane_y = old_plane_x * sin(-rot_speed) + camera->plane_y * cos(-rot_speed);
    }
    
    if (scene->controls.rotate_right) {
        // Rotate counter-clockwise (positive rotation)
        float old_dir_x = camera->dir_x;
        camera->dir_x = camera->dir_x * cos(rot_speed) - camera->dir_y * sin(rot_speed);
        camera->dir_y = old_dir_x * sin(rot_speed) + camera->dir_y * cos(rot_speed);
        
        float old_plane_x = camera->plane_x;
        camera->plane_x = camera->plane_x * cos(rot_speed) - camera->plane_y * sin(rot_speed);
        camera->plane_y = old_plane_x * sin(rot_speed) + camera->plane_y * cos(rot_speed);
    }
}

void handle_movement(t_scene *scene, t_map *map) {
    t_camera *camera = &scene->camera;
    float move_speed = scene->params.trasnlation_speed;
    
    // Clamp movement to maximum 0.9 units per frame (less than 1 cell)
    if (move_speed > 0.9f) {
        move_speed = 0.9f;
    }
    // Forward movement (W key or up arrow)
    if (scene->controls.key_up) {
        float new_x = camera->pos_x + camera->dir_x * move_speed;
        float new_y = camera->pos_y + camera->dir_y * move_speed;
        
        // Check X movement collision
        if (map->map[(int)camera->pos_y][(int)new_x] == '0') {
            camera->pos_x = new_x;
        }
        // Check Y movement collision
        if (map->map[(int)new_y][(int)camera->pos_x] == '0') {
            camera->pos_y = new_y;
        }
    }
    
    // Backward movement (S key or down arrow)
    if (scene->controls.key_down) {
        float new_x = camera->pos_x - camera->dir_x * move_speed;
        float new_y = camera->pos_y - camera->dir_y * move_speed;
        
        // Check X movement collision
        if (map->map[(int)camera->pos_y][(int)new_x] == '0') {
            camera->pos_x = new_x;
        }
        // Check Y movement collision
        if (map->map[(int)new_y][(int)camera->pos_x] == '0') {
            camera->pos_y = new_y;
        }
    }
    
    // Strafe right (D key)
    if (scene->controls.key_left) {
        // Right vector is perpendicular to direction: (dir_y, -dir_x)
        float right_x = camera->dir_y;
        float right_y = -camera->dir_x;
        
        float new_x = camera->pos_x + right_x * move_speed;
        float new_y = camera->pos_y + right_y * move_speed;
        
        // Check X movement collision
        if (map->map[(int)camera->pos_y][(int)new_x] == '0') {
            camera->pos_x = new_x;
        }
        // Check Y movement collision
        if (map->map[(int)new_y][(int)camera->pos_x] == '0') {
            camera->pos_y = new_y;
        }
    }
    
    // Strafe left (A key)
    if (scene->controls.key_right) {
        // Left vector is opposite of right: (-dir_y, dir_x)
        float left_x = -camera->dir_y;
        float left_y = camera->dir_x;
        
        float new_x = camera->pos_x + left_x * move_speed;
        float new_y = camera->pos_y + left_y * move_speed;
        
        // Check X movement collision
        if (map->map[(int)camera->pos_y][(int)new_x] == '0') {
            camera->pos_x = new_x;
        }
        // Check Y movement collision
        if (map->map[(int)new_y][(int)camera->pos_x] == '0') {
            camera->pos_y = new_y;
        }
    }
}

void move_player(t_scene *scene, t_map *map) {
    handle_rotation(scene);
    handle_movement(scene, map);
}
