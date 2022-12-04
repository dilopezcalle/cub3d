/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:22:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/12/04 14:14:16 by almirand         ###   ########.fr       */
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
int		key_hook(int key, t_window	*wndw);
void	get_textures(t_window *wndw, t_content *content);
int		each_frame(t_window *wndw);
void	draw_image(t_window *wndw);
void	build_image(t_window *wndw);
void	clean_buffer(t_window *wndw);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

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

int	init_window(t_content *content)
{
	t_window	wndw;

	wndw.mlx = mlx_init();
	get_player(&wndw, content);
	// DIEGO: Guardar mapa en int en WNDW.map, ya tienes el N,S,E,W a 0, en teoria.
	// wndw.pos_x = 13.0;
	// wndw.pos_y = 3.0;
	wndw.dir_x = -1.0;
	wndw.dir_y = 0.0;
	printf("x: %f\ny: %f\n", wndw.pos_x, wndw.pos_y);
	wndw.plane_x = 0.0;
	wndw.plane_y = 0.66;
	wndw.full_buff = 0;
	wndw.spd_cam = 0.1;
	wndw.spd_move = 0.1;
	if (init_buffer(&wndw) == -1)
		return (-1);
	if (init_texture(&wndw) == -1)
		return (-1);
	get_textures(&wndw, content);
	wndw.content = content;
	int i = 0;
	while (wndw.content->map[i])
	{
		printf("%s\n", wndw.content->map[i]);
		i++;
	}
	wndw.win = mlx_new_window(wndw.mlx, WIDTH, HEIGHT, "KIUB-3D");
	wndw.img.image = mlx_new_image(wndw.mlx, WIDTH, HEIGHT);
	wndw.img.addr = mlx_get_data_addr(wndw.img.image, \
		&wndw.img.bpp, &wndw.img.size, &wndw.img.endian);
	mlx_loop_hook(wndw.mlx, &each_frame, &wndw);
	mlx_hook(wndw.win, 2, 0, &key_hook, &wndw);
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
				wndw->pos_x = (double)x;
				wndw->pos_y = (double)y;
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
