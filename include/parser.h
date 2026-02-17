/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:08:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include <stdint.h>

typedef struct s_data	t_data;
typedef struct s_pos	t_pos;

/*  Parsing */
int			parse_data(t_data *data, char *filename);
void		init_data(t_data *data);
int			parse_sections(t_data *data);
int			handle_element(t_data *data, char *line, int *count);

/* Textures */
int			parse_textures(t_data *data, char *line, int type);
char		*extract_path(char *line);
void		assign_texture(t_data *data, char *path, int type);
int			parse_single_texture(t_data *data, char *line, int type);
int			check_duplicate_texture(t_data *data, int type);

/* Colors */
int			parse_color(t_data *data, char *line, char type);
uint32_t	create_rgb(uint8_t r, uint8_t g, uint8_t b);
int			parse_rgb(char **rgb, uint8_t *r, uint8_t *g, uint8_t *b);
int			extract_color(t_data *data, char *line, char type);

/* Map */
int			parse_map(t_data *data, char *first_line);
int			check_map_line(char *line, t_data *data);
int			is_valid_char(char c);
int			store_map_lines(t_data *data, char **temp, int i);
int			check_player_pos(t_data *data, char c);

/* Validation */
int			valid_map(t_data *data);
int			flood_fill_check(char **map, uint32_t x, uint32_t y);
char		get_map_char(char **map, uint32_t x, uint32_t y);
int			find_player(t_pos *pos, char **map_copy);
int			check_all_elements(t_data *data);

/* Map utils */
int			find_type(char *line);
char		**copy_map(char **map);
uint32_t	get_width(char **map);
uint32_t	get_height(char **map);
int			check_empty_lines_after(int fd);
void		free_temp_map(char **temp, int count);

#endif
