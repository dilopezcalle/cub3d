/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:33:34 by almirand          #+#    #+#             */
/*   Updated: 2022/12/03 17:00:27 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
#include <math.h>

void	get_player_dir(char pos, t_window	*wndw);

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
				content->map[y][x] = 0;
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
	wndw->buff = (unsigned char **)malloc(sizeof(unsigned char *) * HEIGHT);
	if (!(wndw->buff))
		return (-1);
	while (++i < HEIGHT)
	{
		wndw->buff[i] = (unsigned char *)malloc(sizeof(int) * (WIDTH));
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
	wndw->texture = (unsigned char **)malloc(sizeof(unsigned char *) * \
		4);
	if (!wndw->texture)
		return (-1);
	while (++i < 4)
	{
		wndw->texture[i] = (unsigned char *)malloc(sizeof(unsigned char) * \
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
