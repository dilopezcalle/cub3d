/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:43:14 by almirand          #+#    #+#             */
/*   Updated: 2022/12/04 14:14:53 by almirand         ###   ########.fr       */
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

int	worldMap[24][24] =
						{
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
						};

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
		exit(0); //FREE ALL Y MENSAJE
	img->addr = mlx_get_data_addr(img->image, \
		&img->bpp, &img->size, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			txture[y * img->width + x] = (int)img->addr[y * img->width + x];
	}
	mlx_destroy_image(wndw->mlx, img->image);
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
			return (1);
		else
			return (2);
	}
	else
	{
		if (math->ydir > 0)
			return (0);
		else
			return (3);
	}
}

void	draw_textures(t_window	*wndw, t_maths	*math, int x)
{
	int		y;
	int		color;
	int		tex_num;

	y = math->draw_start;
	tex_num = check_sides(math);
	while (y < math->draw_end)
	{
		math->tex_y = (int)math->tex_pos & (TEX_SIZE - 1);
		math->tex_pos += math->step;
		color = wndw->texture[tex_num][TEX_SIZE * math->tex_y + math->tex_x];
		wndw->buff[y][x] = color;
		y++;
	}
}

void	ray_direction(t_maths *math, t_window *wndw)
{
	if (math->xdir < 0)
	{
		math->stepx = -1;
		math->raydist_x = (wndw->pos_x - math->posx) * math->delta_x;
	}
	else
	{
		math->stepx = 1;
		math->raydist_x = (math->posx + 1.0 - wndw->pos_x) * math->delta_x;
	}
	if (math->ydir < 0)
	{
		math->stepy = -1;
		math->raydist_y = (wndw->pos_y - math->posy) * math->delta_y;
	}
	else
	{
		math->stepy = 1;
		math->raydist_y = (math->posy + 1.0 - wndw->pos_y) * math->delta_y;
	}
}

void	wall_hit(t_maths *math, t_window	*wndw)
{
	while (!math->hit)
	{
		if (math->raydist_x < math->raydist_y)
		{
			math->raydist_x += math->delta_x;
			math->posx += math->stepx;
			math->side = 0;
		}
		else
		{
			math->raydist_y += math->delta_y;
			math->posy += math->stepy;
			math->side = 1;
		}
		if (worldMap[math->posy][math->posx] > 0)
			math->hit = 1;
	}
	if (!math->side)
		math->perp_wall_dist = (math->raydist_x - math->delta_x);
	else
		math->perp_wall_dist = (math->raydist_y - math->delta_y);
}
