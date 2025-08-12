#include "../Inc/cube.h"
#include "../libft/libft.h"

e_exit_status handler_texture(char *line, t_map *map, t_mealy *machine)
{
    e_exit_status status;

    line += 3;
    while (*line == ' ')
        line++;
    status = valid_texture(line);
    if (status != SUCCESS)
        return status;

    if (machine->tokens_mask & (1 << machine->current_event))
        return ERR_DUPLICATED_FIELD;
    if (EVENT_TEX_NO == machine->current_event)
        map->texture_no = ft_strdup(line);
    else if (EVENT_TEX_SO == machine->current_event)
        map->texture_so = ft_strdup(line);
    else if (EVENT_TEX_WE == machine->current_event)
        map->texture_we = ft_strdup(line);
    else if (EVENT_TEX_EA == machine->current_event)
        map->texture_ea = ft_strdup(line);
    machine->tokens_mask |= (1 << machine->current_event);
    return SUCCESS;
}

//se puede reducir mucho el parse rgb porque ya sabemos que es valido
e_exit_status handler_color(char *line, t_map *map, t_mealy *machine)
{
    e_exit_status status;
    int rgb_color;
    
    line += 2;
    while (*line == ' ')
        line++;
    status = valid_rgb(line);
    if (status != SUCCESS)
        return status;
    if (machine->tokens_mask & (1 << machine->current_event))
        return ERR_DUPLICATED_FIELD;
    rgb_color = parse_rgb_to_int(line);
    if (rgb_color == -1)
        return ERR_INVALID_RGB;
    if (EVENT_COL_F == machine->current_event)
        map->color_floor = rgb_color;
    else if (EVENT_COL_C == machine->current_event)
        map->color_ceiling = rgb_color;
    machine->tokens_mask |= (1 << machine->current_event);
    return SUCCESS;
}

e_exit_status handler_mapline(char *line, t_map *map, t_mealy *machine)
{
    e_exit_status status;
    char *map_line;
    int width;
    int i;

    status = valid_mapline(line, map, machine, &width);
    if (status != SUCCESS)
        return status;
    map->height++;
    map->map = realloc(map->map, sizeof(char*) * (map->height + 1));
    if (!map->map)
        return ERR_FAIL_MALLOC;
    map_line = (char *)malloc(width + 1);
    if (!map_line)
        return ERR_FAIL_MALLOC;
    i = -1;
    while (++i < width)
        map_line[i] = line[i];
    map_line[width] = '\0';
    map->map[map->height - 1] = map_line;
    map->map[map->height] = NULL;
    if (width > map->width)
        map->width = width;
    return SUCCESS;
}

e_exit_status handler_empty(char *line, t_map *map, t_mealy *machine)
{
    (void)line;
    (void)map;
    (void)machine;
    return SUCCESS;
}

e_exit_status handler_error(char *line, t_map *map, t_mealy *machine)
{
    (void)line;
    (void)map;
    (void)machine;
    return ERR_PARSER;
}

e_exit_status handler_eof(char *line, t_map *map, t_mealy *machine)
{
    (void)line;
    if ((machine->tokens_mask & 0x7F) != 0x7F)
        return ERR_INVALID_MAP;
    if (map->height == 0)
        return ERR_INVALID_MAP;
    return SUCCESS;
}
