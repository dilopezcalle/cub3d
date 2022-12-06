/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:33:34 by almirand          #+#    #+#             */
/*   Updated: 2022/12/06 15:52:47 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
#include <math.h>

void	get_player_dir(char pos, t_window	*wndw)
{
	if (pos == 'S')
	{
		wndw->dir_y = 0.98;
		wndw->plane_x = -0.66;
	}
	else if (pos == 'N')
	{
		wndw->dir_y = -0.98;
		wndw->plane_x = 0.66;
	}
	else if (pos == 'E')
	{
		wndw->plane_y = 0.66;
		wndw->dir_x = -0.98;
	}
	else if (pos == 'W')
	{
		wndw->plane_y = -0.66;
		wndw->dir_x = 0.98;
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
	while (++i < HEIGHT)
	{
		wndw->buff[i] = (int *)malloc(sizeof(int) * (WIDTH));
		if (!(wndw->buff[i]))
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
	wndw->texture = (int **)malloc(sizeof(int *) * \
		4);
	if (!wndw->texture)
		return (-1);
	while (++i < 4)
	{
		wndw->texture[i] = (int *)malloc(sizeof(int) * \
			(TEX_SIZE * TEX_SIZE));
		if (!wndw->texture[i])
			return (-1);
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < TEX_SIZE * TEX_SIZE)
			wndw->texture[i][j] = 0;
	}
	return (0);
}

void	init_maths(t_window *wndw, t_maths *math, int x)
{
	math->cam_x = 2 * x / (double) WIDTH - 1;
	math->xdir = wndw->dir_x + wndw->plane_x * math->cam_x;
	math->ydir = wndw->dir_y + wndw->plane_y * math->cam_x;
	math->posx = (int)wndw->pos_x;
	math->posy = (int)wndw->pos_y;
	if (math->xdir == 0)
		math->delta_x = 1e30;
	else
		math->delta_x = fabs(1 / math->xdir);
	if (math->ydir == 0)
		math->delta_y = 1e30;
	else
		math->delta_y = fabs(1 / math->ydir);
	math->hit = 0;
}

void	init_maths2(t_window	*wndw, t_maths *math)
{
	if (!math->perp_wall_dist)
		math->line_height = (int) HEIGHT;
	else
		math->line_height = (int)(HEIGHT / math->perp_wall_dist);
	math->draw_start = -math->line_height / 2 + HEIGHT / 2;
	if (math->draw_start < 0)
		math->draw_start = 0;
	math->draw_end = math->line_height / 2 + HEIGHT / 2;
	if (math->draw_end >= HEIGHT)
		math->draw_end = HEIGHT - 1;
	math->step = (1.0 * TEX_SIZE / math->line_height);
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
		math->step;
}
