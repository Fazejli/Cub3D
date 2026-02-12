#ifndef PARSER_H
#define PARSER_H

#include "cub3d.h"

typedef struct s_data t_data;
typedef struct s_pos t_pos;

/*  Parsing */
int     parse_data(t_data *data);
void    init_data(t_data *data);
int     parse_sections(t_data *data);
int     find_type(char *line);
int		handle_element(t_data *data, char *line, int *count);

/* Textures */
int		parse_textures(t_data *data, char *line, int type);
char	*extract_path(char *line);
void    assign_texture(t_data *data, char *path, int type);
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
int		is_valid_char(char c);
int		store_map_lines(t_data *data, char *first_line);
int	    check_player_pos(t_data *data, char c);

/* Validation */
int		valid_map(t_data *data);
int		flood_fill_check(char **map, int x, int y, int w, int h);
char	get_map_char(char **map, int x, int y);
int		find_player(t_pos *pos, char **map_copy);
int		check_all_elements(t_data *data);

/* Map utils */
char	**copy_map(char **map);
int		get_width(char **map);
int		get_height(char **map);
int		check_empty_lines_after(int fd);

# endif