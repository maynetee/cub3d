/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:18:34 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:34:26 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define MAX_MAP_LINES 1024
# define MAX_MAP_COLS 1024

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	char		dir;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			invalid_char;
}				t_map;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_color		floor;
	t_color		ceiling;
	int			floor_set;
	int			ceiling_set;
	t_map		map;
	t_player	player;
	int			player_set;
}				t_config;

typedef struct s_collect_data
{
	char		***tmp;
	int			*h;
	int			*cap;
	t_config	*cfg;
}				t_collect_data;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_flood_data
{
	t_map		*map;
	int			*vis;
	t_point		*stack;
	int			*top;
}				t_flood_data;

typedef struct s_dir_map
{
	char		letter;
	double		x;
	double		y;
}				t_dir_map;

int				parse_cub_file(char *path, t_config *cfg);
void			free_config(t_config *cfg);
int				print_error_and_exit(char *msg, t_config *cfg);
int				print_texture_error(char *path, t_config *cfg);
void			free_string_array(char **arr);
int				all_elements_set(t_config *c);
int				check_missing_elements(t_config *c);

int				parse_element_line(char *line, t_config *cfg);
int				parse_floor_line(char **tab, t_config *cfg);
int				parse_ceiling_line(char **tab, t_config *cfg);
void			set_player_direction(t_config *cfg);

int				collect_map_lines(int fd, char *first, t_map *m, t_config *cfg);
int				validate_map_chars_and_player(t_config *cfg);
int				validate_enclosure(t_config *cfg);
int				process_line_and_check_map(char *line, t_config *cfg, int fd);
int				is_map_line(const char *l, int *invalid);
void			strip_newline(char *s);
int				create_padded_grid(t_map *m, char **tmp, int h, t_config *cfg);
int				only_whitespace(char *l);
int				abort_with(char *line, char ***tmp, char *msg, t_config *cfg);
char			**split_identifier(char *trim);
char			**prepare_tokens(char *line, t_config *cfg);
int				validate_numeric_string(char *trim, t_config *cfg);
int				flood_fill(t_map *m, int *vis, int i, int j);
char			*alloc_padded_row(char *src, int width);
int				max_width(char **tmp, int h);
void			cleanup_partial(t_map *m, char **tmp, int h, int i);
int				validate_space_enclosure(t_config *cfg, int i, int j);
int				flood_fill_check(t_config *cfg);
char			*extract_first_token(char *trim, size_t *pos);
size_t			find_value_end(char *trim, size_t start);
char			*extract_value_token(char *trim, size_t start, size_t end);
void			cleanup_tab(char **tab, int count);
int				validate_comma_format(char *rest, t_config *cfg);
int				parse_component(char *s, int *out, t_config *cfg);
int				parse_color_components(char **p, t_color *dst, t_config *cfg);
int				parse_color(char *rest, t_color *dst, t_config *cfg);
int				parse_and_fill_config(const char *path, t_config *cfg);

#endif
