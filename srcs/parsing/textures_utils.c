#include "../../inc/cub3d.h"

int	check_duplicate_texture(t_data *data, int type)
{
	if (type == 1 && data->t_north != NULL)
		return (1);
	if (type == 2 && data->t_south != NULL)
		return (1);
	if (type == 3 && data->t_west != NULL)
		return (1);
	if (type == 4 && data->t_east != NULL)
		return (1);
	return (0);
}

int		assign_texture(t_data *data, char *path, int type)
{
    if (type == 1)
        data->t_north = path;
    if (type == 2)
        data->t_south = path;
    if (type == 3)
        data->t_west = path;
    if (type == 4)
        data->t_east = path;
    return (0);
}

int		check_texture_exists(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

//Verifier si offset est vraiment necessaire
char	*extract_path(char *line, int offset)
{
    int i;
    int start;
    int end;
    char *path;

    i = offset;
    while (ft_isspace(line[i]))
        i++;
    start = i;
    while (line[i] && line[i] != '\n')
        i++;
    end = i;
    while (end > start && ft_isspace(line[end - 1]))
        end --;
    path = ft_substr(line, start, end - start);
    return (path);
}

