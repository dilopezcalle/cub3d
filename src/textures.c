/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:43:14 by almirand          #+#    #+#             */
/*   Updated: 2022/12/08 13:17:59 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minilibx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	get_texture_image(t_window *wndw, int	*txture, \
							char	*path, t_img	*img);
void	init_maths(t_window *wndw, t_maths *math, int x);
void	wall_hit(t_maths *math, t_window	*wndw);
void	ray_direction(t_maths *math, t_window *wndw);
void	init_maths2(t_window	*wndw, t_maths *math);
void	draw_textures(t_window	*wndw, t_maths	*math, int x);
void	exit_free_wndw(t_window *wndw);

void	get_textures(t_window *wndw, t_content *content)
{
	t_img	img;

	get_texture_image(wndw, wndw->texture[0], content->path_no, &img);
	get_texture_image(wndw, wndw->texture[1], content->path_so, &img);
	get_texture_image(wndw, wndw->texture[2], content->path_ea, &img);
	get_texture_image(wndw, wndw->texture[3], content->path_we, &img);
}

void	get_texture_image(t_window *wndw, int	*txture, \
							char	*path, t_img	*img)
{
	int	x;
	int	y;

	img->image = mlx_xpm_file_to_image(wndw->mlx, path, \
		&img->width, &img->height);
	if (img->width != 64 || img->height != 64)
		exit_free_wndw(wndw);
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

void	build_image(t_window *wndw)
{
	int		x;
	t_maths	math;

	x = -1;
	while (++x < WIDTH)
	{
		init_maths(wndw, &math, x);
		ray_direction(&math, wndw);
		wall_hit(&math, wndw);
		init_maths2(wndw, &math);
		draw_textures(wndw, &math, x);
	}
}

int	check_sides(t_maths	*math)
{
	if (!math->side)
	{
		if (math->xdir > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (math->ydir > 0)
			return (1);
		else
			return (0);
	}
}

void	draw_textures(t_window	*wndw, t_maths	*math, int x)
{
	int		y;
	int		color;
	int		tex_num;

	y = -1;
	while (++y < math->draw_start)
	{
		math->tex_y = (int)math->tex_pos & (TEX_SIZE - 1);
		wndw->buff[y][x] = wndw->content->color_ceiling;
	}
	tex_num = check_sides(math);
	while (y < math->draw_end)
	{
		math->tex_y = (int)math->tex_pos & (TEX_SIZE - 1);
		math->tex_pos += math->step;
		color = wndw->texture[tex_num][TEX_SIZE * math->tex_y + math->tex_x];
		wndw->buff[y++][x] = color;
	}
	while (y < HEIGHT)
	{
		math->tex_y = (int)math->tex_pos & (TEX_SIZE - 1);
		wndw->buff[y++][x] = wndw->content->color_floor;
	}
}
