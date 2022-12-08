/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/12/08 11:48:19 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "parser.h"
#include "minilibx/mlx.h"

int		init_window(t_content *content);
void	get_player(t_window *wndw, t_content *content);
void	get_player_dir(char pos, t_window	*wndw);
int		init_buffer(t_window *wndw);
int		init_texture(t_window *wndw);
void	get_textures(t_window *wndw, t_content *content);
int		each_frame(t_window *wndw);
void	draw_image(t_window *wndw);
void	build_image(t_window *wndw);
void	clean_buffer(t_window *wndw);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		key_hook(t_window	*wndw);
int		key_press(int key, t_window *wndw);
int		key_release(int key, t_window *wndw);
int		init_hook(t_window *wndw);
int		exit_free_wndw(t_window *wndw);
int		free_content_struct(t_content *content);
void	free_double_int(int	**array, int x);

int	main(int argc, char *argv[])
{
	t_content	*content;

	if (argc != 2)
		return (printf("Error: Argumentos invalidos\n"));
	content = parser(argv[1]);
	if (!content)
		return (free_content_struct(content));
	if (init_window(content) == -1)
		return (free_content_struct(content));
	return (0);
}

int	init_window(t_content *content)
{
	t_window	wndw;

	wndw.mlx = mlx_init();
	get_player(&wndw, content);
	wndw.spd_cam = 0.05;
	wndw.spd_move = 0.05;
	if (init_buffer(&wndw) == -1)
		return (-1);
	if (init_texture(&wndw) == -1)
		return (free_double_int(wndw.buff, HEIGHT), -1);
	get_textures(&wndw, content);
	wndw.content = content;
	wndw.win = mlx_new_window(wndw.mlx, WIDTH, HEIGHT, "KIUB-3D");
	wndw.img.image = mlx_new_image(wndw.mlx, WIDTH, HEIGHT);
	wndw.img.addr = (int *)mlx_get_data_addr(wndw.img.image, \
		&wndw.img.bpp, &wndw.img.size, &wndw.img.endian);
	init_hook(&wndw);
	mlx_hook(wndw.win, 2, 0, &key_press, &wndw);
	mlx_hook(wndw.win, 17, 0, &exit_free_wndw, &wndw);
	mlx_loop_hook(wndw.mlx, &each_frame, &wndw);
	mlx_hook(wndw.win, 3, 0, &key_release, &wndw);
	mlx_loop(wndw.mlx);
	return (0);
}

void	get_player(t_window *wndw, t_content *content)
{
	int		x;
	int		y;
	char	pos;

	y = -1;
	while (content->map[++y])
	{
		x = 0;
		while (content->map[y][x])
		{
			pos = content->map[y][x];
			if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
			{
				wndw->pos_x = (double)x + 0.5;
				wndw->pos_y = (double)y + 0.5;
				get_player_dir(pos, wndw);
				content->map[y][x] = '0';
				return ;
			}
			x++;
		}
	}
}

int	each_frame(t_window *wndw)
{
	key_hook(wndw);
	build_image(wndw);
	draw_image(wndw);
	clean_buffer(wndw);
	return (0);
}

void	draw_image(t_window *wndw)
{
	int		y;
	int		x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&wndw->img, x, y, wndw->buff[y][x]);
	}
	mlx_put_image_to_window(wndw->mlx, wndw->win, wndw->img.image, 0, 0);
}
