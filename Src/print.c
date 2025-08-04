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

void print_player(t_player player) {
    printf("=== PLAYER DEBUG ===\n");
    printf("offset_x: %.2f\n", player.offset_x);
    printf("offset_y: %.2f\n", player.offset_y);
    printf("ray_x: %.2f\n", player.ray_x);
    printf("ray_y: %.2f\n", player.ray_y);
    printf("angle: %.4f (%.1f°)\n", player.angle, player.angle * 180.0 / PI);
    printf("key_up: %d\n", player.key_up);
    printf("key_down: %d\n", player.key_down);
    printf("key_right: %d\n", player.key_right);
    printf("key_left: %d\n", player.key_left);
    printf("rotate_right: %d\n", player.rotate_right);
    printf("rotate_left: %d\n", player.rotate_left);
    printf("====================\n");
}
