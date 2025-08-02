#include "../Inc/cube.h"
#include "../libft/libft.h"

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
    printf("  Suelo : %s\n", map.color_floor);
    printf("  Techo : %s\n", map.color_celing);

    printf("Jugador:\n");
    printf("  Posición: (%d, %d)\n", map.player_pos[0], map.player_pos[1]);
    printf("  Orientación: ");
    switch (map.orientation) {
        case N: printf("N\n"); break;
        case E: printf("E\n"); break;
        case W: printf("W\n"); break;
        case S: printf("S\n"); break;
        default: printf("Desconocida\n"); break;
    }

    printf("Altura del mapa: %d\n", map.height);

    printf("Anchuras por línea:\n  ");
    for (i = 0; i < map.height; ++i)
        printf("%d ", map.width[i]);
    printf("\n");

    printf("Mapa:\n");
    for (i = 0; i < map.height; ++i)
        printf("%s\n", map.map[i]);
}
