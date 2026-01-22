#include "../../inc/cub3d.h"

int		create_rgb(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

int	ft_atoi_rgb(const char *str, int *error)
{
	int	result;
	int	i;

	while (str[i] && ft_isspace(str[i]))
        i++;
	result = 0;
	*error = 1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (0);
		i++;
	}
    *error = 0;
	while (str[i] && ft_isspace(str[i]))
        i++;
	if (str[i] && str[i] != ',' && str[i] != '\n')
		*error = 1;
	return (result);
}

int		parse_rgb(char **rgb, int *r, int *g, int *b)
{
    int error;

    *r = ft_atoi_rgb(rgb[0], &error);
    if (error)
        return(mess_error("Invalid R value"));
    *g = ft_atoi_rgb(rgb[1], &error);
	if (error)
		return (mess_error("Invalid G value"));
	*b = ft_atoi_rgb(rgb[2], &error);
	if (error)
		return (mess_error("Invalid B value"));
	return (0);
}

int		extract_color(t_data *data, char *line, char type)
{
    char **color;
    int r;
    int g;
    int b;
    int i = 0;

    while (line[i] && line[i] == type)
        i++;
    while (ft_isspace(line[i]))
        i++;
    color = ft_split(&line[i], ',');
    if (!color || !color[0] || !color[1] || !color[2] || !color[3])
        return (free_split(color), mess_error("Invalid RGB format"));
    if (parse_rgb(color, &r, &g, &b))
        return (free_split(color), 1);
    free_split(color);
    if (type == 'F')
        data->floor_color = create_rgb(r, g, b);
    else
        data->ceiling_color = create_rgb(r, g, b);
    return (0);
}

int parse_color(t_data *data, char *line, char type)
{
    if (type == 'F' && data->floor_color != -1)
        return (mess_error("Duplicate floor color"));
    if (type == 'C' && data->floor_color != -1)
        return (mess_error("Duplicate ceiling color"));
    return (extract_color(data, line, type));
}
