#include "../Inc/cube.h"
#include "../libft/libft.h"

// Normalizar anchos del mapa eliminando espacios finales innecesarios
void normalize_map(t_map *map) {
    int max_width = 0;
    int i, j;
    
    // Encontrar el ancho máximo real
    for (i = 0; i < map->height; i++) {
        if (map->width[i] > max_width)
            max_width = map->width[i];
    }
    
    // Recortar espacios finales de cada fila
    for (i = 0; i < map->height; i++) {
        j = map->width[i] - 1;
        while (j >= 0 && map->map[i][j] == ' ')
            j--;
        
        // Actualizar width real (sin espacios finales)
        map->width[i] = j + 1;
        map->map[i][j + 1] = '\0';
    }
}

// Flood fill para verificar que el mapa está cerrado
e_exit_status flood_fill(t_map *map, int x, int y, char **visited) {
    // Límites del mapa
    if (y < 0 || y >= map->height || x < 0 || x >= map->width[y])
        return ERR_INVALID_MAP;
    
    // Si llegamos a un borde y es espacio, el mapa está abierto
    if (map->map[y][x] == ' ')
        return ERR_INVALID_MAP;
    
    // Si es pared o ya visitado, OK
    if (map->map[y][x] == '1' || visited[y][x])
        return SUCCESS;
    
    // Marcar como visitado
    visited[y][x] = 1;
    
    // Flood fill recursivo en 4 direcciones
    if (flood_fill(map, x + 1, y, visited) != SUCCESS ||
        flood_fill(map, x - 1, y, visited) != SUCCESS ||
        flood_fill(map, x, y + 1, visited) != SUCCESS ||
        flood_fill(map, x, y - 1, visited) != SUCCESS)
        return ERR_INVALID_MAP;
    
    return SUCCESS;
}

e_exit_status validate_map(t_map *map) {
    char **visited;
    e_exit_status status;
    int i;
    
    // Normalizar el mapa
    normalize_map(map);
    
    // Verificar que hay al menos una línea
    if (map->height == 0)
        return ERR_INVALID_MAP;
    
    // Crear matriz de visitados
    visited = malloc(sizeof(char*) * map->height);
    if (!visited)
        return ERR_FAIL_MALLOC;
    
    for (i = 0; i < map->height; i++) {
        visited[i] = ft_calloc(map->width[i], sizeof(char));
        if (!visited[i]) {
            // Liberar memoria ya allocada
            while (--i >= 0)
                free(visited[i]);
            free(visited);
            return ERR_FAIL_MALLOC;
        }
    }
    
    // Flood fill desde la posición del jugador
    status = flood_fill(map, map->player_pos[0], map->player_pos[1], visited);
    
    // Liberar memoria de visitados
    for (i = 0; i < map->height; i++)
        free(visited[i]);
    free(visited);
    
    return status;
}
