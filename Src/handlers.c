#include "../Inc/cube.h"
#include "../libft/libft.h"

e_exit_status handler_texture(char *line, t_map *map, t_mealy *machine) {
    e_exit_status status;
    
    printf("Ejecutando el handler: texture\n");
    line += 3;
    while (*line == ' ')
        line++;
    
    // Validar textura
    status = valid_texture(line);
    if (status != SUCCESS)
        return status;
    
    // Verificar duplicado
    if (machine->tokens_mask & (1 << machine->current_event))
        return ERR_DUPLICATED_FIELD;
    
    // Asignar textura según evento
    if (EVENT_TEX_NO == machine->current_event)
        map->texture_no = ft_strdup(line);
    else if (EVENT_TEX_SO == machine->current_event)
        map->texture_so = ft_strdup(line);
    else if (EVENT_TEX_WE == machine->current_event)
        map->texture_we = ft_strdup(line);
    else if (EVENT_TEX_EA == machine->current_event)
        map->texture_ea = ft_strdup(line);
    
    // Marcar como procesado
    machine->tokens_mask |= (1 << machine->current_event);
    
    return SUCCESS;
}

//se puede reducir mucho el parse rgb porque ya sabemos que es valido
e_exit_status handler_color(char *line, t_map *map, t_mealy *machine) {
    e_exit_status status;
    int rgb_color;
    
    printf("Ejecutando el handler: color\n");
    line += 2;
    while (*line == ' ')
        line++;
    
    // Validar RGB
    status = valid_rgb(line);
    if (status != SUCCESS)
        return status;
    
    // Verificar duplicado
    if (machine->tokens_mask & (1 << machine->current_event))
        return ERR_DUPLICATED_FIELD;
    
    // Parsear RGB a entero
    rgb_color = parse_rgb_to_int(line);
    if (rgb_color == -1)
        return ERR_INVALID_RGB;
    
    // Asignar color según evento
    if (EVENT_COL_F == machine->current_event)
        map->color_floor = rgb_color;
    else if (EVENT_COL_C == machine->current_event)
        map->color_ceiling = rgb_color;
    
    // Marcar como procesado
    machine->tokens_mask |= (1 << machine->current_event);
    
    return SUCCESS;
}

e_exit_status handler_mapline(char *line, t_map *map, t_mealy *machine) {
    e_exit_status status;
    char *map_line;
    int width;
    int i;
    
    printf("Ejecutando el handler: mapline\n");
    
    // Validar mapline
    status = valid_mapline(line, map, machine, &width);
    if (status != SUCCESS)
        return status;
    
    // Realloc para nueva línea del mapa + NULL terminator
    map->map = realloc(map->map, sizeof(char*) * (map->height + 2));
    if (!map->map)
        return ERR_FAIL_MALLOC;
    
    // Realloc para nuevo width
    map->width = realloc(map->width, sizeof(int) * (map->height + 1));
    if (!map->width)
        return ERR_FAIL_MALLOC;
    
    // Copiar línea sin \n
    map_line = malloc(width + 1);
    if (!map_line)
        return ERR_FAIL_MALLOC;
    
    for (i = 0; i < width; i++)
        map_line[i] = line[i];
    map_line[width] = '\0';
    
    // Asignar a la estructura
    map->map[map->height] = map_line;
    map->map[map->height + 1] = NULL;
    map->width[map->height] = width;
    map->height++;
    
    return SUCCESS;
}

e_exit_status handler_empty(char *line, t_map *map, t_mealy *machine) {
    (void)line; (void)map; (void)machine;
    printf("Ejecutando el handler: empty\n");
    return SUCCESS;
}

e_exit_status handler_error(char *line, t_map *map, t_mealy *machine) {
    (void)line; (void)map; (void)machine;
    printf("Ejecutando el handler: error\n");
    return ERR_PARSER;
}

e_exit_status handler_eof(char *line, t_map *map, t_mealy *machine) {
    printf("Ejecutando el handler: eof\n");
    (void)line;
    
    // Verificar que todos los tokens requeridos están presentes
    // 0x7F = 0b01111111 (6 tokens + 1 jugador)
    if ((machine->tokens_mask & 0x7F) != 0x7F)
        return ERR_INVALID_MAP;
    
    // Verificar que hay al menos una línea de mapa
    if (map->height == 0)
        return ERR_INVALID_MAP;
    
    return SUCCESS;
}
