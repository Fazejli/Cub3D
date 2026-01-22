#include "../../inc/cub3d.h"

int elements_section(char *line)
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

int parse_file(t_data *data)
{
    char *line;
    int   compt = 0;
    int     type;

    while (compt < 6)
    {
        line = gnl(data->fd);
        if (!line)
            return (1);
        if (ft_is_empty(line))
        {
            free(line);
            continue;
        }
        type = elements_section(line);
        if (type > 0)
        {
            if (parse_textures(data, line, type))
                return(free(line), 1);
            compt++;
        }
        else
        {
            if (parse_map(data, line))
                return (1);
        }
    }
    free(line);
    return (0);
}

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

int    parse_data(t_data *data)
{
    init_data(data);
    if (parse_file(data))
        return (1);
    return (0);
}