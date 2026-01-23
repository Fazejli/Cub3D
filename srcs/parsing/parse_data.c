#include "../../inc/cub3d.h"

int find_type(char *line)
{
    int i = 0;

    while (line[i] && ft_isspace(line[i]))
        i++;
    if (ft_strncmp(&line[i], "NO ", 3) == 0)
        return (1);
    if (ft_strncmp(&line[i], "SO ", 3) == 0)
        return (2);
    if (ft_strncmp(&line[i], "WE ", 3) == 0)
        return (3);
    if (ft_strncmp(&line[i], "EA ", 3) == 0)
        return (4);
    if (ft_strncmp(&line[i], "F ", 2) == 0)
        return (5);
    if (ft_strncmp(&line[i], "C ", 2) == 0)
        return (6);
    return (0);
}

int handle_element(t_data *data, char *line, int *count)
{
    int type;

    type = find_type(line);
    if (type > 0)
    {
        if (parse_textures(data, line, type))
            return (1);
        (*count)++;
        return (0);
    }
    return (-1);
}
/*
int parse_sections(t_data *data)
{
    char *line;
    int   compt = 0;

    while (compt < 6)
    {
        line = gnl(data->fd);
        if (!line)
            return (1);
        if (!ft_is_empty(line))
        {
            if (handle_element(data, line, &compt) == -1)
				return (free(line), mess_error("Invalid element"));
        }
        free(line);
    }
    if (!check_all_elements(data))
        return (mess_error("Missing elements."));
    return (0);
}*/

void    init_data(t_data *data)
{
    data->t_north = NULL;
    data->t_south = NULL;
    data->t_west = NULL;
    data->t_east = NULL;
    data->floor_color = -1;
    data->ceiling_color = -1;
    data->map = NULL;
    data->player_pos = NULL;
    data->fd = 0;
}
/*
int    parse_data(t_data *data)
{
    char *line;

    init_data(data);
    if (parse_sections(data))
        return (1);
    while (1)
    {
        line = gnl(data->fd);
        if (!line)
            return(mess_error("No map found"));
        if (!ft_is_empty(line))
        {
            if (parse_map(data, line))
                return (free(line), 1);
            free(line);
            break ;
        }
        free(line);
    }
    if (valid_map(data))
        return (1);
    return (0);
}*/

// Dans parse_data.c, ajoutez des traces :

int parse_sections(t_data *data)
{
    char *line;
    int   compt = 0;

    printf("DEBUG: Starting parse_sections\n");
    while (compt < 6)
    {
        printf("DEBUG: Reading element %d/6\n", compt + 1);
        line = gnl(data->fd);
        if (!line)
        {
            printf("DEBUG: gnl returned NULL at element %d\n", compt);
            return (1);
        }
        printf("DEBUG: Read line: [%s]\n", line);
        if (!ft_is_empty(line))
        {
            if (handle_element(data, line, &compt) == -1)
            {
                printf("DEBUG: Invalid element\n");
                return (free(line), mess_error("Invalid element"));
            }
            printf("DEBUG: Element %d parsed successfully\n", compt);
        }
        else
            printf("DEBUG: Empty line skipped\n");
        free(line);
    }
    printf("DEBUG: parse_sections completed\n");
    if (!check_all_elements(data))
        return (mess_error("Missing elements."));
    return (0);
}

int parse_data(t_data *data)
{
    char *line;
    int line_count = 0;

    printf("DEBUG: Starting parse_data\n");
    init_data(data);
    if (parse_sections(data))
        return (1);
    
    printf("DEBUG: Looking for map...\n");
    while (1)
    {
        line_count++;
        printf("DEBUG: Reading line %d for map\n", line_count);
        line = gnl(data->fd);
        if (!line)
        {
            printf("DEBUG: gnl returned NULL, no map found\n");
            return(mess_error("No map found"));
        }
        printf("DEBUG: Read: [%s]\n", line);
        if (!ft_is_empty(line))
        {
            printf("DEBUG: Found map start\n");
            if (parse_map(data, line))
                return (free(line), 1);
            free(line);
            break ;
        }
        free(line);
        if (line_count > 100)
        {
            printf("DEBUG: Too many lines, stopping\n");
            return (mess_error("Infinite loop detected"));
        }
    }
    printf("DEBUG: Validating map\n");
    if (valid_map(data))
        return (1);
    return (0);
}
