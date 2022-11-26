/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:43:14 by almirand          #+#    #+#             */
/*   Updated: 2022/11/26 17:35:25 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minilibx/mlx.h"

void	floor_cast(t_window *wndw, t_maths *math, int x, int y);
void	get_texture_image(t_window *wndw, unsigned char	*txture, \
							char	*path, t_img	*img);
void	init_maths(t_window *wndw, t_maths *math, int y);
void	init_maths2(t_window *wndw, t_maths *math, int x);
int		minilibx_color(int r, int g, int b);
void	wall_hit(t_maths *math, t_window *wndw);
void	ray_direction(t_maths *math, t_window *wndw);

void	get_textures(t_window *wndw, t_content *content)
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
}

void	build_image(t_window *wndw)
{
	t_maths	math;
	int		y;
	int		x;

	//tal vez reiniciar buff a 0
	y = -1;
	while (++y < HEIGHT)
	{
		init_maths(wndw, &math, y);
		x = -1;
		while (++x < WIDTH)
			floor_cast(wndw, &math, x, y);
	}
	x = -1;
	while (++x < WIDTH)
	{
		init_maths2(wndw, &math, x);
		ray_direction(&math, wndw);
		wall_hit(&math, wndw);
	}
}

void	floor_cast(t_window *wndw, t_maths *math, int x, int y)
{
	math->text_x = (int)(TEX_SIZE * (math->leftx_column - \
		(int)math->leftx_column)) & (TEX_SIZE - 1);
	math->text_y = (int)(TEX_SIZE * (math->lefty_column - \
		(int)math->lefty_column)) & (TEX_SIZE - 1);
	math->leftx_column += math->row_dist * \
		(math->xdir_right - math->xdir_left) / WIDTH;
	math->lefty_column += math->row_dist * \
		(math->ydir_right - math->ydir_left) / WIDTH;
	//TO DO: Comprobar colores
	wndw->buff[y][x] = minilibx_color(104, 188, 60); //SUELO: Editar para cargar texturas wndw->textures[4][TEXT_SIZE * math->text_y + math->text_x]
	wndw->buff[HEIGHT - y -1][x] = minilibx_color(104, 188, 235); //CIELO: simetrco a altura de pantalla - y - 1, en vez de y
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
		//Check ray hit
		if (wndw->content->map[math->posx][math->posy] > 0)
			math->hit = 1;
	}
	if (!math->side)
		math->perp_wall_dist = (math->posx - wndw->pos_x + \
			(1 - math->stepx) / 2) / math->xdir;
	else
		math->perp_wall_dist = (math->posy - wndw->pos_y + \
			(1 - math->stepy) / 2) / math->ydir;
}
