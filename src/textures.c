/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:43:14 by almirand          #+#    #+#             */
/*   Updated: 2022/12/03 17:06:20 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minilibx/mlx.h"
#include <math.h>
#include <stdio.h>

void	floor_cast(t_window *wndw, t_maths *math, int x, int y);
void	get_texture_image(t_window *wndw, unsigned char	*txture, \
							char	*path, t_img	*img);
void	init_maths(t_window *wndw, t_maths *math, int x);
int		minilibx_color(int r, int g, int b);
void	wall_hit(t_maths *math, t_window *wndw);
void	ray_direction(t_maths *math, t_window *wndw);
void	floor_walls(t_maths	*math, t_window	*wndw);
void	floor_draw(t_maths	*math, t_window	*wndw, int x);
void	init_maths2(t_window	*wndw, t_maths *math);
void	draw_textures(t_window	*wndw, t_maths	*math, int x);

void	get_textures(t_window	*wndw)
{
	int	x;
	int	y;
	int	xorcolor;
	int	xycolor;
	int	ycolor;

	x = -1;
	while (++x < TEX_SIZE)
	{
		y = -1;
		while (++y < TEX_SIZE)
		{
			xorcolor = (x * 256 / TEX_SIZE) ^ (y * 256 / TEX_SIZE);
			ycolor = y * 256 / TEX_SIZE;
			xycolor = y * 128 / TEX_SIZE + x * 128 / TEX_SIZE;
			wndw->texture[0][TEX_SIZE * y + x] = 65536 * 254 * (x != y && x != TEX_SIZE - y);
			wndw->texture[1][TEX_SIZE * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			wndw->texture[2][TEX_SIZE * y + x] = 256 * xycolor + 65536 * xycolor;
			wndw->texture[3][TEX_SIZE * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
		}
	}
}

/* void	get_textures(t_window *wndw, t_content *content)
{
	t_img	img;

	get_texture_image(wndw, wndw->texture[0], content->path_no, &img);
	get_texture_image(wndw, wndw->texture[1], content->path_so, &img);
	get_texture_image(wndw, wndw->texture[2], content->path_ea, &img);
	get_texture_image(wndw, wndw->texture[3], content->path_we, &img);
}

void	get_texture_image(t_window *wndw, unsigned char	*txture, \
							char	*path, t_img	*img)
{
	int	x;
	int	y;

	img->image = mlx_xpm_file_to_image(wndw->mlx, path, \
		&img->width, &img->height); //TO DO: Si height y width no son 64x64 puede dar error. Hacer exit
	img->addr = (unsigned char *)mlx_get_data_addr(img->image, \
		&img->bpp, &img->size, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			txture[y * img->width + x] = img->addr[y * img->width + x];
	}
} */

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

void	draw_textures(t_window	*wndw, t_maths	*math, int x)
{
	int	y;
	int	color;
	int	tex_num;

	y = math->draw_start;
	tex_num = 1;
	while (y < math->draw_end)
	{
		math->tex_y = (int)math->tex_pos & (TEX_SIZE - 1);
		math->tex_pos += (1.0 * TEX_SIZE / math->line_height); //lINE HEIGHT mal, division /0 por perp;
		color = wndw->texture[tex_num][TEX_SIZE * math->tex_y + math->tex_x];
		if (math->side)
			color = (color >> 1) & 8355711;
		wndw->buff[y][x] = color;
		y++;
	}
}

void	init_maths2(t_window	*wndw, t_maths *math)
{
	if (math->perp_wall_dist == 0)
		math->line_height = HEIGHT; //invent
	else
		math->line_height = (int)(HEIGHT / math->perp_wall_dist);
	math->draw_start = (-math->line_height / 2) + (HEIGHT / 2);
	if (math->draw_start < 0)
		math->draw_start = 0;
	math->draw_end = (math->line_height / 2) + (HEIGHT / 2);
	if (math->draw_end >= HEIGHT)
		math->draw_end = HEIGHT - 1;
	if (!math->side)
		math->wall_x = wndw->pos_y + math->perp_wall_dist * math->ydir;
	else
		math->wall_x = wndw->pos_x + math->perp_wall_dist * math->xdir;
	math->wall_x -= floor(math->wall_x);
	math->tex_x = (int)(math->wall_x * (double)TEX_SIZE);
	if (math->side == 0 && math->xdir > 0)
		math->tex_x = TEX_SIZE - math->tex_x - 1;
	if (math->side == 1 && math->ydir < 0)
		math->tex_x = TEX_SIZE - math->tex_x - 1;
	math->tex_pos = (math->draw_start - HEIGHT / 2 + math->line_height / 2) * \
		(1.0 * TEX_SIZE / math->line_height);
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

void	wall_hit(t_maths *math, t_window *wndw)
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
		if (wndw->content->map[math->posy][math->posx] > 0)
			math->hit = 1;
	}
	if (!math->side)
		math->perp_wall_dist = (math->raydist_x - math->delta_x);
	else
		math->perp_wall_dist = (math->raydist_y - math->delta_y);
}
