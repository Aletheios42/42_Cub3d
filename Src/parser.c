#include "../Inc/cube.h"
#include "../libft/libft.h"


e_exit_code parser(t_map *map, char **map_path)
{
    (void)map;
    (void)map_path;
    map->map = (char **)malloc(11 * sizeof(char *));
    if (!map->map)
        return ERR_FAIL_MALLOC;
    map->map[0] = "1111111111";
    map->map[1] = "1000000001";
    map->map[2] = "1000000001";
    map->map[3] = "1000000001";
    map->map[4] = "1000000001";
    map->map[5] = "1010000001";
    map->map[6] = "1001000001";
    map->map[7] = "1000000001";
    map->map[8] = "1000000101";
    map->map[9] = "1111111111";
    map->map[10] =  0x0;

    return SUCCESS;
}
