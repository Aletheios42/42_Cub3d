#include "../Inc/cube.h"
#include "../libft/libft.h"

int get_common_initial_space(t_map *map)
{
    int num_common_spaces;
    int i;
    int j;

    num_common_spaces = INT_MAX;
    i = -1;
    while (++i < map->height)
    {
        j = 0;
        while (map->map[i][j] == ' ' && j < num_common_spaces)
            j++;
        if (j < num_common_spaces)
            num_common_spaces = j;
    }
    return num_common_spaces;
}
e_exit_status normalize_map(t_map *map)
{
    char *normalized_line = NULL;
    int num_common_spaces;
    int i;
    int j;

    num_common_spaces = get_common_initial_space(map);
    i = -1;
    //tengo que normalizar aquí
    while (++i < map->height)
    {
        j = -1;
        normalized_line = (char *)malloc(sizeof(char *) * (map->width + 1));
        if (!normalized_line)
            return ERR_FAIL_MALLOC;
        while (map->map[i][++j + num_common_spaces])
            normalized_line[j] = map->map[i][j + num_common_spaces]; 
        while (j < map->width)
            normalized_line[j++] = ' ';
        normalized_line[j] = '\0';
        free(map->map[i]);
        map->map[i] = normalized_line;
    }
    return SUCCESS;
}

e_exit_status flood_fill(t_map *map, char **visited, int row, int col)
{
    if (row >= map->height || row < 0 || col < 0 || col >= map->width)
        return printf("out of bounds\n"),ERR_MAP_IS_NOT_CLOSE;
    if (map->map[row][col] == ' ')
        return printf("espacio encontrado\n"),ERR_MAP_IS_NOT_CLOSE;
    if (visited[row][col] == '1' || map->map[row][col] == '1' )
        return SUCCESS;

    visited[row][col] = '1';

    if (SUCCESS != flood_fill(map, visited, row - 1, col))
        return ERR_MAP_IS_NOT_CLOSE;
    if (SUCCESS != flood_fill(map, visited, row + 1, col))
        return ERR_MAP_IS_NOT_CLOSE;
    if (SUCCESS != flood_fill(map, visited, row, col + 1))
        return ERR_MAP_IS_NOT_CLOSE;
    if (SUCCESS != flood_fill(map, visited, row, col - 1))
        return ERR_MAP_IS_NOT_CLOSE;
    return SUCCESS;

}

e_exit_status check_map_is_closed(t_map *map) {
    e_exit_status status;
    char **visited;
    int i;
    int line_size;

    visited = (char **)malloc((map->height + 1) * (sizeof(char *)));
    if (!visited)
        return ERR_FAIL_MALLOC;
    i = -1;
    while (++i < map->height)
    {
        line_size = ft_strlen(map->map[i]);
        visited[i] = (char *)malloc((line_size + 1) * sizeof(char));
        if (!visited[i])
            return ft_free_matrix(visited) ,ERR_FAIL_MALLOC;
        ft_memset(visited[i], '0', line_size);
        visited[i][line_size] = '\0';
    }
    visited[i] = NULL;
    status = flood_fill(map, visited, map->player_pos[1], map->player_pos[0]);
    ft_free_matrix(visited);
    return status;
}

e_exit_status validate_map(t_map *map) {
    e_exit_status status;

    status = normalize_map(map);
    if (SUCCESS != status)
        return status;
    status = check_map_is_closed(map);
    return status;
}
