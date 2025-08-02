#include "../Inc/cube.h"
#include "../libft/libft.h"

t_event get_event_type(char *line) {
    if (!line)
        return EVENT_EOF;
    else if (ft_strncmp(line, "NO ", 3) == 0)
        return EVENT_TEX_NO;
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return EVENT_TEX_SO;
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return EVENT_TEX_WE;
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return EVENT_TEX_EA;
    else if (ft_strncmp(line, "F ", 2) == 0)
        return EVENT_COL_F;
    else if (ft_strncmp(line, "C ", 2) == 0)
        return EVENT_COL_C;
    else if (ft_strncmp(line, "\n", 2) == 0)
        return EVENT_EMPTY;
    else if (line[0] == '1' || line[0] == ' ' || line[0] == ' ')
        return EVENT_MAP_LINE;
    return EVENT_INVALID;
}

t_state (*get_matrix())[EVENT_COUNT] {
                       // [EVENT_TEX_NO, EVENT_TEX_SO, EVENT_TEX_WE, EVENT_TEX_EA, EVENT_COL_C,  EVENT_COL_F, EVENT_MAP_LINE,EVENT_EMPTY, EVENT_INVALID, EVENT_EOF]
    static t_state matrix[STATE_COUNT][EVENT_COUNT] = {
        [STATE_START]  = { STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_ERR,    STATE_START, STATE_ERR,  STATE_ERR },
        [STATE_HEADER] = { STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_HEADER, STATE_MAP,    STATE_HEADER, STATE_ERR,  STATE_END },
        [STATE_MAP]    = { STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_MAP,    STATE_END,    STATE_ERR,  STATE_END },
        [STATE_ERR]    = { STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,    STATE_ERR,  STATE_ERR },
        [STATE_END]    = { STATE_END,    STATE_END,    STATE_END,    STATE_END,    STATE_END,    STATE_END,    STATE_END,    STATE_END,    STATE_END,  STATE_END }
    };
    return matrix;
}

t_handler (*get_outputs())[EVENT_COUNT] {
                        // [EVENT_TEX_NO,    EVENT_TEX_SO,   EVENT_TEX_WE,   EVENT_TEX_EA,    EVENT_COL_C,    EVENT_COL_F,   EVENT_MAP_LINE,  EVENT_EMPTY,  EVENT_INVALID, EVENT_EOF]
    static t_handler outputs[STATE_COUNT][EVENT_COUNT] = {
        [STATE_START]  = { handler_texture, handler_texture, handler_texture, handler_texture, handler_color, handler_color, handler_error,   handler_empty, handler_error, handler_eof  },
        [STATE_HEADER] = { handler_texture, handler_texture, handler_texture, handler_texture, handler_color, handler_color, handler_mapline, handler_empty, handler_error, handler_eof  },
        [STATE_MAP]    = { handler_error,   handler_error,   handler_error,   handler_error,   handler_error, handler_error, handler_mapline, handler_empty, handler_error, handler_eof  },
        [STATE_ERR]    = { handler_error,   handler_error,   handler_error,   handler_error,   handler_error, handler_error, handler_error,   handler_error, handler_error, handler_error },
        [STATE_END]    = { handler_eof,     handler_eof,     handler_eof,     handler_eof,     handler_eof,   handler_eof,   handler_eof,     handler_eof,   handler_eof,   handler_eof   }
    };
    return outputs;
}


t_mealy get_machine(void) {
    static t_mealy machine;

    machine.transitions = get_matrix();
    machine.outputs = get_outputs();
    machine.current_state = STATE_START;
    machine.current_event = EVENT_INVALID;
    machine.tokens_mask = 0;

    return machine;
}

e_exit_status parser(t_map *map, char *map_path) {
    char *line;
    int fd;
    e_exit_status status;
    t_mealy machine;
    
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return ERR_OPEN;
    machine = get_machine();
    int i = 0;
    while (machine.current_state != STATE_END && machine.current_state != STATE_ERR) {
        line = get_next_line(fd);
        printf("\n ============== \n");
        printf("Linea[%d]: %s", ++i, line);
        machine.current_event = get_event_type(line);
        printf("Evento[%d]: %i\n", i, machine.current_event);
        machine.current_state = machine.transitions[machine.current_state][machine.current_event];
        printf("Estado[%d]: %i\n", i, machine.current_state);
        status = machine.outputs[machine.current_state][machine.current_event](line, map, &machine);
        if (line)
            free(line);
        if (SUCCESS != status)
            break;
    }
    close(fd);
    if (status == SUCCESS && machine.current_state == STATE_END)
        status = validate_map(map);
    return status;
}
