#include "../Inc/cube.h"
#include "../libft/libft.h"

void free_map(t_map *map) {
    int i;
    
    if (!map)
        return;
    
    // Liberar texturas
    if (map->texture_no) {
        free(map->texture_no);
        map->texture_no = NULL;
    }
    if (map->texture_so) {
        free(map->texture_so);
        map->texture_so = NULL;
    }
    if (map->texture_we) {
        free(map->texture_we);
        map->texture_we = NULL;
    }
    if (map->texture_ea) {
        free(map->texture_ea);
        map->texture_ea = NULL;
    }
    
    // Liberar colores
    if (map->color_floor) {
        free(map->color_floor);
        map->color_floor = NULL;
    }
    if (map->color_celing) {
        free(map->color_celing);
        map->color_celing = NULL;
    }
    
    // Liberar mapa
    if (map->map) {
        for (i = 0; map->map[i]; i++) {
            free(map->map[i]);
        }
        free(map->map);
        map->map = NULL;
    }
    
    // Liberar array de widths
    if (map->width) {
        free(map->width);
        map->width = NULL;
    }
    
    // Resetear valores
    map->height = 0;
}
