/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/12/03 16:29:36 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "parser.h"
#include "keys.h"
#include "minilibx/mlx.h"

int		init_window(t_content *content);
void	get_player(t_window *wndw, t_content *content);
int		init_buffer(t_window *wndw);
int		init_texture(t_window *wndw);
int		key_hook(int key, t_window	*wndw);
int		key_hook2(int key, t_window	*wndw);
int		key_hook3(int key, t_window	*wndw);
void	get_textures(t_window *wndw, t_content *content);
void	get_texture_image(t_window *wndw, unsigned char	*txture, \
		char	*path, t_img	*img);
int		each_frame(t_window *wndw);
void	draw_image(t_window *wndw);
void	build_image(t_window *wndw);

int	main(int argc, char *argv[])
{
	t_content	*content;

	if (argc != 2)
		return (printf("Error: Argumentos invalidos\n"));
	content = parser(argv[1]);
	if (!content)
	{
		free(content);
		return (1);
	}
	if (init_window(content) == -1)
	{
		free(content);
		return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	unsigned char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	init_window(t_content *content)
{
	t_window	wndw;

	wndw.mlx = mlx_init();
	get_player(&wndw, content);
	wndw.plane_x = 0.0;
	wndw.plane_y = 0.66;
	wndw.full_buff = 0;
	wndw.spd_cam = 0.05;
	wndw.spd_move = 0.05;
	if (init_buffer(&wndw) == -1)
		return (-1);
	if (init_texture(&wndw) == -1)
		return (-1);
	get_textures(&wndw, content);
	wndw.content = content;
	wndw.win = mlx_new_window(wndw.mlx, WIDTH, HEIGHT, "KIUB-3D");
	wndw.img.image = mlx_new_image(wndw.mlx, WIDTH, HEIGHT);
	wndw.img.addr = (unsigned char *)mlx_get_data_addr(wndw.img.image, \
		&wndw.img.bpp, &wndw.img.size, &wndw.img.endian);
	mlx_loop_hook(wndw.mlx, &each_frame, &wndw);
	mlx_hook(wndw.win, 2, 0, &key_hook, &wndw);
	mlx_loop(wndw.mlx);
	return (0);
}

int	key_hook(int key, t_window	*wndw)
{
	if (key == W_U)
	{
		if (!wndw->content->map[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)])
			wndw->pos_x += wndw->dir_x * wndw->spd_move;
		if (!wndw->content->map[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x])
			wndw->pos_y += wndw->dir_y * wndw->spd_move;
	}
	else if (key == S_D)
	{
		if (!wndw->content->map[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)])
			wndw->pos_x -= wndw->dir_x * wndw->spd_move;
		if (!wndw->content->map[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x])
			wndw->pos_y -= wndw->dir_y * wndw->spd_move;
	}
	return (key_hook2(key, wndw));
}

int	key_hook2(int key, t_window	*wndw)
{
	if (key == D_R)
	{
		wndw->aux_dirx = wndw->dir_x;
		wndw->dir_x = wndw->dir_x * cos(-wndw->spd_cam) - \
			wndw->dir_y * sin(-wndw->spd_cam);
		wndw->dir_y = wndw->aux_dirx * sin(-wndw->spd_cam) + \
			wndw->dir_y * cos(-wndw->spd_cam);
		wndw->aux_planex = wndw->plane_x;
		wndw->plane_x = wndw->plane_x * cos(-wndw->spd_cam) - \
			wndw->plane_y * sin(-wndw->spd_cam);
		wndw->plane_y = wndw->aux_planex * sin(-wndw->spd_cam) + \
			wndw->plane_y * cos(-wndw->spd_cam);
	}
	return (key_hook3(key, wndw));
}

int	key_hook3(int key, t_window	*wndw)
{
	if (key == A_L)
	{
		wndw->aux_dirx = wndw->dir_x;
		wndw->dir_x = wndw->dir_x * cos(wndw->spd_cam) - \
			wndw->dir_y * sin(wndw->spd_cam);
		wndw->dir_y = wndw->aux_dirx * sin(wndw->spd_cam) + \
			wndw->dir_y * cos(wndw->spd_cam);
		wndw->aux_planex = wndw->plane_x;
		wndw->plane_x = wndw->plane_x * cos(wndw->spd_cam) - \
			wndw->plane_y * sin(wndw->spd_cam);
		wndw->plane_y = wndw->aux_planex * sin(wndw->spd_cam) + \
			wndw->plane_y * cos(wndw->spd_cam);
	}
	if (key == ESC)
	{
		exit(0); //TO DO: FREE ALL
	}
	mlx_clear_window(wndw->mlx, wndw->win);
	return (0);
}

void	clean_buffer(t_window *wndw)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			wndw->buff[y][x] = 0;
	}
}

int	each_frame(t_window *wndw)
{
	build_image(wndw);
	draw_image(wndw);
	clean_buffer(wndw);
	return (0);
}

void	draw_image(t_window *wndw)
{
	int		y;
	int		x;
	t_img	img;

	img.image = mlx_new_image(wndw->mlx, WIDTH, HEIGHT);
	img.addr = (unsigned char *)mlx_get_data_addr(img.image, \
		&img.bpp, &img.size, &img.endian);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&img, x, y, wndw->buff[y][x]);
	}
	mlx_put_image_to_window(wndw->mlx, wndw->win, img.image, 0, 0);
}
