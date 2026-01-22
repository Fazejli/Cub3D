#ifndef PARSER_H
#define PARSER_H

#include "cub3d.h"

/*  Parsing */
int     parse_data(t_data *data);
void    init_data(t_data *data);
int     parse_file(t_data *data);
int     elements_section(char *line);
int		handle_element(t_data *data, char *line, int *count);

/* Textures */
int		parse_textures(t_data *data, char *line, int type);
char	*extract_path(char *line, int offset);
int		check_texture_exists(char *path);
int		assign_texture(t_data *data, char *path, int type);
int		parse_single_texture(t_data *data, char *line, int type);
int	    check_duplicate_texture(t_data *data, int type);

/* Colors */
int		parse_color(t_data *data, char *line, char type);
int		create_rgb(int r, int g, int b);
int		ft_atoi_rgb(const char *str, int *error);
int		parse_rgb(char **rgb, int *r, int *g, int *b);
int		extract_color(t_data *data, char *line, char type);

/* Map */
int		parse_map(t_data *data, char *first_line);
int		check_map_line(char *line, t_data *data);
int		is_valid_map_char(char c);
int		store_map_lines(t_data *data, char *first_line);
int		check_player_char(char c, t_data *data);

/* Validation */
int		validate_map(t_data *data);
int		flood_fill_check(char **map, int x, int y, int w, int h);
char	get_map_char(char **map, int x, int y);
int		find_player_and_validate(t_data *data, char **map_copy);
int		check_all_elements_present(t_data *data);

/* Map utils */
int		get_map_width(char **map);
int		get_map_height(char **map);
char	**copy_map(char **map);
void	free_map(char **map);
int		check_empty_lines_after(int fd);

# endif