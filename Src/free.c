#include "../Inc/cube.h"
#include "../libft/libft.h"

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->texture_no)
        free(map->texture_no);
    if (map->texture_so)
        free(map->texture_so);
    if (map->texture_we)
        free(map->texture_we);
    if (map->texture_ea)
        free(map->texture_ea);
    if (map->map)
    {
        i = -1;
        while (map->map[++i])
            free(map->map[i]);
        free(map->map);
    }
    ft_memset(map, 0, sizeof(t_map));
}

