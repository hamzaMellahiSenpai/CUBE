/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:08:43 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 00:55:54 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# if defined(__APPLE__)
#  include "minilibx/key_macos.h"
# else
#  include "minilibx/key_linux.h"
# endif
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "mlx.h"
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# define SWIDTH g_screen.width
# define SHEIGHT g_screen.height
# define VIEW_ANGLE (float)1.0472
# define WALL 1
# define RED 0XFF0000
# define BUFFER_SIZE 1
# define PP g_world.player.position
# define WALKDIRECTION g_world.player.walk_direction
# define TURNDIRECTION g_world.player.turn_direction
# define PROTATIONSPEED g_world.player.rotation.speed
# define PROTATIONANGLE g_world.player.rotation.angle
# define PLAYERNAME g_world.player.name
# define PLAYERPOS g_world.player.position
# define PLAYERPOSINMMAP g_world.player.pos_in_map
# define PLAYERH g_world.player.height
# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define BLOCK_SIZE 64
# define PLAYERRJ g_world.player.rj
# define MINIMAP_SCALE SWIDTH * 0.00009
# define DEG(x) x * 180 / M_PI

enum			e_states
{
	UNCOMPLETED,
	FAIL
};

enum			e_images
{
	SPRITE,
	TEXTURE
};

enum			e_file_infos
{
	north_texture,
	south_texture,
	east_texture,
	west_texture,
	sprite_texture,
	resolution,
	floor_color,
	ceil_color,
	map,
	player_position,
};

enum			e_errors
{
	INVALID_FILE_NAME,
	MISSING_INFO,
	DUPLICATE_TEXTURE,
	DUPLICATE_COLOR,
	DUPLICATE_RESOLUTION,
	DRAWING_OUTSIDE_IMAGE,
	INVALID_MAP,
	NON_EXISTENECE_FILE,
	Allocation_Failed,
	PROCCESS_CANT_BE_CREATED,
	INVALID_PATH,
	INVALID_SPRITE_PLACEMENT,
	INVALID_RESOLUTION,
	DUPLICATE_PLAYER,
	INVALID_SPRITE_ARG,
	INVALID_COLORS,
	DUPLICATE_SPRITE,
	SUBPROCESS
};

enum			e_space
{
	skybox,
	ground
};

typedef char*	t_string;

typedef	struct	s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef	struct	s_pair
{
	void	*a;
	void	*b;
}				t_pair;

typedef	struct	s_shape
{
	int		width;
	int		height;
}				t_shape;

typedef struct	s_lst
{
	void			*content;
	struct s_lst	*next;
}				t_lst;

typedef	struct	s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
	int color;
}				t_color;

typedef	struct	s_rotation
{
	float angle;
	float speed;
}				t_rotation;

typedef struct	s_player
{
	t_vector			position;
	t_rotation			rotation;
	float				speed;
	t_vector			view;
	int					lives;
	int					walk_direction;
	int					turn_direction;
	float				offset;
	int					maxlives;
	int					coins;
	int					height;
	char				name;
	t_vector			pos_in_map;
	int					rj;
}				t_player;

typedef struct	s_ray
{
	float		angle;
	float		distance;
	int			is_facing_down;
	int			is_facing_right;
	int			color;
	int			is_facing_left;
	int			is_facing_up;
	int			type;
	t_vector	wall_hit;
	int			is_hor_hit;
	int			hor_found;
	int			ver_found;
	t_vector	dis_to_object;
}				t_ray;

typedef struct	s_image
{
	void		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	int			*data;
	float		stepy;
	float		stepx;
	t_vector	size;
	char		*path;
	float		x;
	float		y;
	float		endx;
	float		endy;
	float		z;
	float		f;
	float		endz;
	float		endf;
	int			ignored_color;
	float		size_in_screen;
}				t_image;

typedef	struct	s_animation
{
	int		is_play_on_awake;
	int		is_loop;
	int		is_running;
	int		nofframes;
	int		currentframe;
	int		fps;
	int		is_playing;
}				t_animation;

typedef struct	s_sprite
{
	t_image			img;
	float			distance;
	t_vector		pos;
	t_string		path;
	float			size;
	float			s_x;
	float			s_y;
	int				visible;
	t_vector		pos_in_map;
	t_animation		anim;
	unsigned int	bc;
	int				y_offset;
	int				type;
}				t_sprite;

typedef struct	s_world
{
	int					rows;
	int					cols;
	int					is_game_paused;
	int					show_mini_map;
	t_player			player;
	int					sky_box_color;
	int					ground_color;
	t_sprite			*sprites;
	int					sprites_count;
	int					colors[2];
	t_ray				*wall_rays;
	t_lst				*adresses;
	int					numofsprites;
	int					gravity;
	char				**map;
	int					is_game_over;
	int					only_exit;
	int					bc_music_pid;
	int					frame;
	int					is_bc_music_played;
	t_image				pause_menu;
	t_image				coin;
	t_image				lives_bar;
	t_image				coins_count_img;
	t_image				hearts_img;
	char				*valid_chars_in_map;
}				t_world;

typedef	struct	s_texture
{
	int		*data;
	int		width;
	int		height;
}				t_texture;

typedef	struct	s_time
{
	float		old_time;
	float		current_time;
	float		delta_time;
}				t_time;

void			*g_mlx;
void			*g_window;
t_world			g_world;
int				g_is_keypressed;
t_shape			g_screen;
int				g_infos[10];
t_image			g_textures[20];
t_string		g_messages[18];
void			check_for_file(t_string file_name);
void			draw_img(t_image img);
t_image			new_img(t_string	path);
t_vector		new_vector(float x, float y);
void			add_to_vector(t_vector *a, t_vector *b);
t_vector		add_vectors(t_vector a, t_vector b);
t_vector		multi_vector_to_n(t_vector a, float b);
t_vector		multi_vectors(t_vector a, t_vector b);
void			print_vector(t_vector vector);
void			update_field_of_view();
void			direct_line(int x, int start, int end, int color);
void			render_texture(t_image texture, int wall_height,
				int col, t_ray ray);
void			render_sprite(t_sprite sprite);
float			dist(t_vector a, t_vector b);
void			save_first_frame_in_bmp_file();
int				tablen(void **tab);
void			update_col_name(t_string line);
int				handle_input(int key, void *p);
void			update_player();
float			deg_to_rad(int angle);
void			put_pixel(t_vector a, int color);
void			rect(t_vector position, float width, float height, int color);
void			draw_square(float row, float col, float grid_size, float color);
int				move_player(int key, void *p);
void			background(int color);
void			get_delta_time();
float			norm_angle(float angle);
int				wall_at(t_vector coordinate);
void			cast(t_ray *ray);
t_ray			new_ray(float ray_angle);
void			render_walls();
void			circle(t_vector a, int radius, int color);
int				get_next_line(int fd, char **line);
int				ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2, int index);
char			*ft_strcpy(char *dest, const char *src);
void			free_space(char **ptr);
int				ft_atoi(const char *str);
void			*ft_memset(void *p, int val, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int nbr);
int				numofdigits(int n);
int				ft_isdigit(char c);
int				tablen(void **tab);
int				isnumber(t_string str);
char			*trim(char const *s, char const *set);
int				ft_strcmp(const char *s1, const char *s2);
void			handle_error(int error_index, int status);
void			init_errors();
void			cube(t_vector a, int width, int color);
float			dist(t_vector a, t_vector b);
int				rgb_to_int(int r, int g, int b);
void			draw_mini_map();
t_string		ft_strlcat(char *dst, const char *src);
int				update();
int				key_pressed(int key_code, void *p);
int				key_released(int key_code, void *p);
void			push_back(t_lst **alst, t_lst *new);
t_lst			*new_lst(void *content);
void			deletelist(t_lst **head_ref);
t_pair			*make_pair(void *a, void *b);
void			push_front(t_lst **head_ref, t_lst *new);
t_image			load_image(int i, t_string path, int type);
int				is_out_of_window(t_vector a);
int				shadow(int color, float distance);
void			sort_sprites();
void			show_sprites();
void			update_sprites();
void			*sf_malloc(size_t size);
void			*sf_realloc(void *ptr, size_t size);
void			free_all(int status);
int				wall_at(t_vector coordinate);
void			text(char *str, int x, int y, int color);
int				mouse(int x, int y);
char			*trim(char const *s1, char const *set);
void			load_texture(t_string line, int index);
void			load_sprite(t_string line);
void			read_color(t_string line, int index, int space);
void			read_image(t_string line, int index);
void			read_resolution(t_string line);
void			validate_args(t_string **args, int nargs, int signal);
void			check_for_info(t_string line);
int				is_info_full();
void			read_file(t_string file_name);
void			get_player_pos(int col, int row, char c);
void			get_rows_cols(t_string file_name);
void			check_closed_map();
void			allocate_map();
void			fill_map(t_string file_name, t_string line);
int				is_secret_door(t_vector coordinate);
void			draw_hud();
int				create_coins_count(int c, int len_nbr,
				int offset_x, int coin_size);
int				create_coins();
void			draw_lives_bar();
int				look_for_sp(int x, int y);
int				play_music(t_string	path);
void			update_sprite_frames(void);
void			do_bonus_part();
int				exit_hook(void);
void			line(float x0, float y0, float x1, float y1);
int				object_at(t_vector coordinate);
#endif
