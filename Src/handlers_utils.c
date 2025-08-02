#include "../Inc/cube.h"
#include "../libft/libft.h"

e_exit_status valid_texture(char *line) {
    char *tmp;
    int fd;
    
    // Verificar extensión .xmp
    tmp = ft_strnstr(line, ".xpm", ft_strlen(line));
    if (!tmp)
        return ERR_BAD_EXTENSION;
    
    // Verificar formato válido después de .xpm
    tmp += 4;
    if (*tmp != '\n' && *tmp != '\0')
        return ERR_INVALID_TEXTURE;
    
    // Eliminar \n si existe
    *tmp = '\0';
    
    // Verificar que el archivo existe y es accesible
    fd = open(line, O_RDONLY);
    if (fd < 0)
        return ERR_INVALIAD_ROUTE_MAP;
    close(fd);
    
    return SUCCESS;
}

e_exit_status valid_rgb(char *line) {
    char *tmp;
    int color;
    int i;
    
    tmp = line;
    i = -1;
    while (++i < 3) {
        color = ft_atoi(tmp);
        if (color < 0 || color > 255)
            return ERR_INVALID_COLOR_RANGE;
        while (ft_isdigit(*tmp))
            tmp++;
        if (i < 2) {
            if (*tmp != ',')
                return ERR_INVALID_COLOR_FORMAT;
            tmp++;
        }
    }
    while (*tmp == ' ')
        tmp++;
    if (*tmp != '\n' && *tmp != '\0')
        return ERR_INVALID_COLOR_FORMAT;
    
    if (*tmp == '\n')
        *tmp = '\0';
    
    return SUCCESS;
}

e_exit_status valid_mapline(char *line, t_map *map, t_mealy *machine, int *width) {
    char *tmp;
    
    tmp = line;
    *width = 0;
    
    while (*tmp && *tmp != '\n') {
        if (!ft_strchr("01 NSEW", *tmp))
            return ERR_INVALID_MAP_CHAR;
        
        // Verificar orientación única
        if (ft_strchr("NSEW", *tmp) && (machine->tokens_mask & (1 << 6)))
            return ERR_DUPLICATED_PLAYER;
        
        if (ft_strchr("NSEW", *tmp)) {
            // Guardar posición y orientación
            map->player_pos[0] = *width;
            map->player_pos[1] = map->height;
            if (*tmp == 'N') map->orientation = N;
            else if (*tmp == 'S') map->orientation = S;
            else if (*tmp == 'E') map->orientation = E;
            else if (*tmp == 'W') map->orientation = W;
            
            machine->tokens_mask |= (1 << 6);
        }
        tmp++;
        (*width)++;
    }
    
    return SUCCESS;
}
