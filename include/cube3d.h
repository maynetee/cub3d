#ifndef CUBE3D_H
# define CUBE3D_H

# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdio.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FOV 66

# ifdef __APPLE__
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
# else
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
# endif

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}	t_direction;

typedef enum e_element_type
{
	NO_TEX = 0,
	SO_TEX = 1,
	WE_TEX = 2,
	EA_TEX = 3,
	FLOOR_COLOR = 4,
	CEILING_COLOR = 5
}	t_element_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
}	t_color;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_scene
{
	char		**map;
	int			map_width;
	int			map_height;
	char		*texture_paths[4];
	t_color		floor_color;
	t_color		ceiling_color;
	int			elements_found;
}	t_scene;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_scene		scene;
	t_player	player;
	t_texture	textures[4];
}	t_game;

/* Parsing functions */
int		parse_scene_file(char *filename, t_scene *scene);
int		parse_scene_elements(int fd, t_scene *scene);
int		parse_texture_line(char *line, t_scene *scene);
int		parse_color_line(char *line, t_scene *scene);
int		parse_map_data(int fd, t_scene *scene);

int		validate_map_format(t_scene *scene);
int		validate_map_walls(t_scene *scene);
int		validate_player_position(t_scene *scene);
int		find_player_in_map(t_scene *scene, int *x, int *y, char *dir);
int		check_map_characters(t_scene *scene);

int		validate_texture_files(t_scene *scene);
int		validate_color_values(t_color *color);
int		validate_scene_elements(t_scene *scene);
int		check_file_extension(char *filename, char *extension);
int		check_texture_accessibility(char *path);

/* Graphics functions */
int		init_mlx_window(t_game *game);
int		init_mlx_image(t_game *game);
int		setup_mlx_hooks(t_game *game);
int		close_window(t_game *game);
int		handle_mlx_error(t_game *game);

int		load_texture_files(t_game *game);
int		load_single_texture(t_game *game, int index, char *path);
int		validate_texture_data(t_texture *texture);
int		convert_texture_data(t_texture *texture);
int		free_texture_resources(t_texture *texture);

void	render_walls(t_game *game, t_ray *ray, int x);
void	draw_wall_stripe(t_game *game, t_ray *ray, int x);
void	calculate_texture_coords(t_ray *ray, t_texture *tex, int *tex_x);
void	draw_floor_ceiling(t_game *game, int x, t_ray *ray);
int		get_texture_pixel(t_texture *tex, int x, int y);

/* Raycasting functions */
void	perform_dda_algorithm(t_ray *ray, char **map);
void	init_ray_parameters(t_ray *ray, t_player *player, int x);
void	calculate_step_and_side_dist(t_ray *ray, t_player *player);
void	execute_dda_steps(t_ray *ray, char **map);
void	calculate_wall_distance(t_ray *ray, t_player *player);

void	render_frame(t_game *game);
void	cast_rays_for_frame(t_game *game);
void	calculate_wall_height(t_ray *ray);
void	determine_wall_texture(t_ray *ray, int *texture_index);
void	clear_frame_buffer(t_game *game);

/* Player functions */
int		init_player_position(t_game *game);
void	set_player_direction(t_player *player, char direction);
int		find_player_spawn(t_scene *scene, t_player *player);
void	calculate_initial_plane(t_player *player);
int		validate_player_spawn(t_scene *scene);

int		move_player_forward(t_game *game);
int		move_player_backward(t_game *game);
int		move_player_left(t_game *game);
int		move_player_right(t_game *game);
int		rotate_player(t_game *game, double rotation_angle);

/* Input functions */
int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		process_movement_keys(int keycode, t_game *game);
int		process_rotation_keys(int keycode, t_game *game);
int		handle_exit_key(int keycode, t_game *game);

/* Core functions */
int		main(int argc, char **argv);
int		initialize_game(t_game *game, char *scene_file);
int		validate_arguments(int argc, char **argv);
int		setup_game_components(t_game *game);
void	run_game_loop(t_game *game);

int		game_loop(t_game *game);
void	update_game_state(t_game *game);
void	render_game_frame(t_game *game);
int		calculate_frame_time(void);
void	limit_frame_rate(int frame_time);

/* Utility functions */
void	cleanup_game_resources(t_game *game);
void	cleanup_scene_data(t_scene *scene);
void	cleanup_texture_data(t_game *game);
void	cleanup_mlx_resources(t_game *game);
int		safe_exit(t_game *game, int exit_code);

void	print_error(char *message);
void	print_usage(void);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup_safe(const char *s);
int		create_color_hex(int r, int g, int b);

/* Additional parsing helper functions */
char	**add_line_to_map(char **map, char *line, int line_count);
char	*process_map_line(char *line);
int		calculate_map_width(char **map, int height);
int		normalize_map_lines(t_scene *scene);
char	*pad_line_with_spaces(char *line, int target_width);
int		is_surrounded_by_walls(t_scene *scene, int y, int x);
int		is_valid_map_char(char c);
int		check_map_characters(t_scene *scene);

#endif