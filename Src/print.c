#include "../Inc/cube.h"
void print_map(t_map map) {
    int i;

    printf("\n");
    printf("PRINT MAP:\n");

    printf("Texturas:\n");
    printf("  NO: %s\n", map.texture_no);
    printf("  SO: %s\n", map.texture_so);
    printf("  WE: %s\n", map.texture_we);
    printf("  EA: %s\n", map.texture_ea);

    printf("Colores:\n");
    printf("  Suelo : %d\n", map.color_floor);
    printf("  Techo : %d\n", map.color_ceiling);

    printf("Jugador:\n");
    printf("  Posición: (%d, %d)\n", map.player_pos[0], map.player_pos[1]);
    printf("  Orientación: %c\n", map.orientation);

    printf("Dimensiones:\n Altura[%d] Anchura[%d]\n", map.height, map.width);
    printf("\n");

    printf("Mapa:\n");
    for (i = 0; i < map.height; ++i)
        printf("%s\n", map.map[i]);
}

void print_mlx(t_mlx mlx) {
    printf("=== MLX DEBUG ===\n");
    printf("mlx: %p\n", mlx.mlx);
    printf("win: %p\n", mlx.win);
    printf("img: %p\n", mlx.img);
    printf("addr: %p\n", mlx.addr);
    printf("bpp: %d\n", mlx.bpp);
    printf("lpl: %d\n", mlx.lpl);
    printf("endian: %d\n", mlx.endian);
    printf("=================\n");
}

void print_scene(t_scene scene) {
    printf("=== Scene ===\n");

    printf("Controls:\n");
    printf("  key_up: %s\n", scene.controls.key_up ? "true" : "false");
    printf("  key_down: %s\n", scene.controls.key_down ? "true" : "false");
    printf("  key_right: %s\n", scene.controls.key_right ? "true" : "false");
    printf("  key_left: %s\n", scene.controls.key_left ? "true" : "false");
    printf("  rotate_right: %s\n", scene.controls.rotate_right ? "true" : "false");
    printf("  rotate_left: %s\n", scene.controls.rotate_left ? "true" : "false");

    printf("Parameters:\n");
    printf("  rotation_speed: %.6f\n", scene.params.rotation_speed);
    printf("  translation_speed: %d\n", scene.params.trasnlation_speed);
    printf("  block_size: %d\n", scene.params.block_size);
    printf("  fieldOfView: %.6f\n", scene.params.fieldOfView);

    printf("Camera:\n");
    printf("  pos_x: %.6f\n", scene.camera.pos_x);
    printf("  pos_y: %.6f\n", scene.camera.pos_y);
    printf("  dir_x: %.6f\n", scene.camera.dir_x);
    printf("  dir_y: %.6f\n", scene.camera.dir_y);
    printf("  plane_x: %.6f\n", scene.camera.plane_x);
    printf("  plane_y: %.6f\n", scene.camera.plane_y);
}

void print_dda(t_dda dda) {
    printf("=== DDA State ===\n");

    printf("Map position:     map_x = %d, map_y = %d\n", dda.map_x, dda.map_y);

    printf("Ray direction:    rayDir_x = %.6f, rayDir_y = %.6f\n",
           dda.rayDir_x, dda.rayDir_y);

    printf("Side distances:   sideDist_x = %.6f, sideDist_y = %.6f\n",
           dda.sideDist_x, dda.sideDist_y);

    printf("Delta distances:  deltaDist_x = %.6f, deltaDist_y = %.6f\n",
           dda.deltaDist_x, dda.deltaDist_y);

    printf("Wall distance:    wallDist = %.6f\n", dda.wallDist);

    printf("Step:             step_x = %d, step_y = %d\n",
           dda.step_x, dda.step_y);

    printf("Hit:              %s\n", dda.hit ? "true" : "false");
    printf("Side:             %d\n", dda.side);
}
