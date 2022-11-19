/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/19 15:52:02 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "structs.h"
#include "parser.h"
#include "keys.h"
#include "minilibx/mlx.h"

int		init_window(t_content *content);
void	get_player(t_window *wndw, t_content *content);
void	get_player_dir(char pos, t_window	*wndw);
int		init_buffer(t_window *wndw);
int		init_texture(t_window *wndw);
int		key_hook(int key, t_window	*wndw);
void	get_textures(t_window *wndw, t_content *content);
void	get_texture_image(t_window *wndw, int	*txture, char	*path, t_img	*img);
int		each_frame(t_window *wndw);

int	main(int argc, char *argv[])
{
	t_content	*content;

	if (argc != 2)
		return (printf("Error: Argumentos invalidos\n"));
	content = parser(argv[1]);
	if (!content)
		return (1);
	if (init_window(content) == -1)
		return (1);
	return (0);
}

/** BASURA DE ALAIN **/
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
	wndw.win = mlx_new_window(wndw.mlx, WIDTH, HEIGHT, "KIUB-3D");
	wndw.img.image = mlx_new_image(wndw.mlx, WIDTH, HEIGHT);
	wndw.img.addr = (int *)mlx_get_data_addr(wndw.img.image, &wndw.img.bpp, \
		&wndw.img.size, &wndw.img.endian);
	//mlx_loop_hook(wndw.mlx, &each_frame, &wndw);
	//mlx_hook(wndw.win, 2, 0, &key_hook, &wndw);
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
				wndw->pos_x = x;
				wndw->pos_y = y;
				get_player_dir(pos, wndw);
				return ;
			}
			x++;
		}
	}
}

void	get_player_dir(char pos, t_window	*wndw)
{
	if (pos == 'N')
	{
		wndw->dir_y = 1.0;
		wndw->dir_x = 0.0;
	}
	else if (pos == 'S')
	{
		wndw->dir_y = -1.0;
		wndw->dir_x = 0.0;
	}
	else if (pos == 'E')
	{
		wndw->dir_y = 0.0;
		wndw->dir_x = -1.0;
	}
	else if (pos == 'W')
	{
		wndw->dir_y = -1.0;
		wndw->dir_x = 0.0;
	}
}

int	init_buffer(t_window	*wndw)
{
	int	i;
	int	j;

	i = -1;
	wndw->buff = (int **)malloc(sizeof(int *) * HEIGHT);
	if (!(wndw->buff))
		return (-1);
	while (++i < WIDTH)
	{
		wndw->buff[i] = (int *)malloc(sizeof(int) * (WIDTH));
		if (!(wndw->buff))
			return (-1);
	}
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			wndw->buff[i][j] = 0;
	}
	return (0);
}

int	init_texture(t_window	*wndw)
{
	int	i;
	int	j;

	i = -1;
	wndw->texture = (int **)malloc(sizeof(int *) * TEX_SIZE);
	if (!wndw->texture)
		return (-1);
	while (++i < 4)
	{
		wndw->texture[i] = (int *)malloc(sizeof(int) * (TEX_SIZE * TEX_SIZE));
		if (!wndw->texture)
			return (-1);
	}
	i = -1;
	while (++i < TEX_SIZE)
	{
		j = -1;
		while (++j < TEX_SIZE)
			wndw->texture[i][j] = 0;
	}
	return (0);
}

int	key_hook(int key, t_window	*wndw)
{
	if (key == A_L)
	{
	}
	else if (key == S_D)
	{
	}
	else if (key == S_D)
	{
	}
	else if (key == S_D)
	{
	}
	else if (key == ESC)
	{
		exit(0); //TO DO: FREE ALL
	}
	mlx_clear_window(wndw->mlx, wndw->win);
	return (0);
}

void	get_textures(t_window *wndw, t_content *content)
{
	t_img	img;

	get_texture_image(wndw, wndw->texture[0], content->path_no, &img);
	get_texture_image(wndw, wndw->texture[1], content->path_so, &img);
	get_texture_image(wndw, wndw->texture[2], content->path_ea, &img);
	get_texture_image(wndw, wndw->texture[3], content->path_we, &img);
}

void	get_texture_image(t_window *wndw, int	*txture, char	*path, t_img	*img)
{
	int	x;
	int	y;

	img->image = mlx_xpm_file_to_image(wndw->mlx, path, \
		&img->width, &img->height);
	img->addr = (int *)mlx_get_data_addr(img->image, \
		&img->bpp, &img->size, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			txture[y * img->width + x] = img->addr[y * img->width + x];
	}
}

/* int	each_frame(t_window *wndw)
{
	build_image(wndw);
	draw_image(wndw);
	return (0);
}
 */
