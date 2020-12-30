/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 04:22:02 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 03:18:08 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int *g_p;
t_image g_img;

void	init_world(void)
{
	g_world.player.walk_direction = 0;
	g_world.player.turn_direction = 0;
	g_world.player.rotation.speed = 5 * 0.0174533;
	g_world.player.speed = 40;
	g_world.player.offset = 0;
	g_world.player.coins = 100;
	g_world.player.maxlives = 3;
	g_world.player.lives = 1;
	g_world.player.rj = 0;
	g_world.gravity = 0;
	g_world.is_game_over = BONUS ? 1 : 0;
	g_world.is_game_paused = 0;
	g_world.show_mini_map = 0;
	g_world.frame = 0;
	g_world.pause_menu = new_img("pause_menu.xpm");
	g_world.hearts_img = new_img("hearts.xpm");
	g_world.valid_chars_in_map = ft_strdup(BONUS ? "10NWSE D" : "10NWSE 2");
	g_is_keypressed = 0;
}

t_image	new_img(t_string path)
{
	t_image img;

	img = load_image(4, ft_strjoin("assets/textures/", path, 2), TEXTURE);
	img.size = new_vector(SWIDTH, SHEIGHT);
	img.path = path;
	img.x = 0;
	img.y = 0;
	img.f = 0;
	img.z = 0;
	img.endx = img.size.x;
	img.endy = img.size.y;
	img.endz = 0;
	img.ignored_color = 0;
	return (img);
}

void	setup(void)
{
	init_world();
	g_window = mlx_new_window(g_mlx, g_screen.width, g_screen.height, "cub3D");
	g_img.img = mlx_new_image(g_mlx, g_screen.width, g_screen.height);
	g_p = (int *)mlx_get_data_addr(g_img.img, &g_img.bits_per_pixel,
	&g_img.size_line, &g_img.endian);
	g_world.wall_rays = sf_malloc(sizeof(t_ray) * (g_screen.width + 1));
	update_player();
	update_sprites();
	update_field_of_view();
	render_walls();
	show_sprites();
	create_coins(&g_world.coin);
	g_world.coins_count_img = new_img("chars.xpm");
	if (BONUS)
	{
		draw_img(new_img("main_menu.xpm"));
		g_world.bc_music_pid =
		play_music("assets/sounds/GNT.mp3");
		g_world.is_bc_music_played = 1;
	}
	mlx_put_image_to_window(g_mlx, g_window, g_img.img, 0, 0);
}

int		update(int key)
{
	(void)key;
	if (g_world.is_game_over)
		return (0);
	if (g_world.is_game_paused)
	{
		draw_img(g_world.pause_menu);
		mlx_put_image_to_window(g_mlx, g_window, g_img.img, 0, 0);
		return (0);
	}
	update_player();
	update_sprites();
	update_field_of_view();
	render_walls();
	show_sprites();
	if (BONUS)
		do_bonus_part();
	mlx_put_image_to_window(g_mlx, g_window, g_img.img, 0, 0);
	background(0);
	g_world.frame++;
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		perror("NOT VALID NUMBER OF ARGS");
		exit(FAIL);
	}
	g_world.numofsprites = 0;
	g_world.player.rotation.angle = M_PI;
	g_infos[9] = 0;
	g_mlx = mlx_init();
	read_file(av[1]);
	setup();
	if (ac == 3 && ft_strcmp(av[2], "--save") == 0)
	{
		save_first_frame_in_bmp_file();
		free_all(UNCOMPLETED);
	}
	mlx_loop_hook(g_mlx, update, (void*)0);
	if (BONUS)
		mlx_hook(g_window, 6, 0, mouse, (void*)0);
	mlx_hook(g_window, 2, (1L << 0), key_pressed, (void*)0);
	mlx_hook(g_window, 3, (2L << 0), key_released, (void*)0);
	mlx_hook(g_window, 17, 0, exit_hook, (void*)0);
	mlx_loop(g_mlx);
	return (0);
}
