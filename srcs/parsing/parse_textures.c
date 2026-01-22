#include "../../inc/cub3d.h"

int		parse_single_texture(t_data *data, char *line, int type)
{
    char *path;
    
    if (check_duplicate_texture(data, type))
		return (mess_error("Duplicate texture"));
    path = extract_path(line, 2);
    if (!path)
        return (mess_error("Path extraction failed"));
    if (!check_texture_exists(path))
    {
        free(path);
        return (mess_error("Texture file not found"));
    }
    return (assign_texture(data, path, type));
}

int		parse_textures(t_data *data, char *line, int type)
{
    if (type >= 1 && type <= 4)
        return (parse_single_texture(data, line, type));
    else if (type == 5)
        return (parse_color(data, line, 'F'));
    else if (type == 6)
        return (parse_color(data, line, 'C'));
    return (mess_error("Invalid element's identifier"));
}