#include "../Inc/cube.h"
#include "../libft/libft.h"

// Normalizar anchos del mapa eliminando espacios finales e iniciales innecesarios
void normalize_map(t_map *map) {
    int min_leading_spaces = INT_MAX;
    int i, j;
    
    // Encontrar el mínimo de espacios iniciales
    for (i = 0; i < map->height; i++) {
        int leading_spaces = 0;
        while (leading_spaces < map->width[i] && map->map[i][leading_spaces] == ' ')
            leading_spaces++;
        
        // Solo considerar filas no vacías
        if (leading_spaces < map->width[i] && leading_spaces < min_leading_spaces)
            min_leading_spaces = leading_spaces;
    }
    
    // Si no hay contenido, no normalizar
    if (min_leading_spaces == INT_MAX)
        min_leading_spaces = 0;
    
    // Procesar cada fila
    for (i = 0; i < map->height; i++) {
        // Remover espacios iniciales comunes
        if (min_leading_spaces > 0) {
            int new_width = map->width[i] - min_leading_spaces;
            if (new_width > 0) {
                ft_memmove(map->map[i], map->map[i] + min_leading_spaces, new_width);
                map->width[i] = new_width;
            } else {
                map->map[i][0] = '\0';
                map->width[i] = 0;
            }
        }
        
        // Recortar espacios finales
        j = map->width[i] - 1;
        while (j >= 0 && map->map[i][j] == ' ')
            j--;
        
        // Actualizar width real y terminar string
        map->width[i] = j + 1;
        if (map->width[i] >= 0)
            map->map[i][map->width[i]] = '\0';
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
