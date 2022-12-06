/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 10:08:09 by almirand          #+#    #+#             */
/*   Updated: 2022/12/06 15:54:02 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "keys.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "minilibx/mlx.h"

int	key_hook2(int key, t_window	*wndw);
int	key_hook3(int key, t_window	*wndw);

int	key_hook(int key, t_window	*wndw)
{
	char	**gworldMap = wndw->content->map;
	double	aux_x;
	double	aux_y;

	aux_x = wndw->pos_x;
	aux_y = wndw->pos_y;
	if (key == W_U)
	{
		if ((gworldMap[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)]) == '0')
			wndw->pos_x += wndw->dir_x * wndw->spd_move;
		if ((gworldMap[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y += wndw->dir_y * wndw->spd_move;
	}
	if (key == S_D)
	{
		if ((gworldMap[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)]) == '0')
			wndw->pos_x -= wndw->dir_x * wndw->spd_move;
		if ((gworldMap[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y -= wndw->dir_y * wndw->spd_move;
	}
	if (gworldMap[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)] == '1' && gworldMap[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x] == '1')
	{
		wndw->pos_x = aux_x;
		wndw->pos_y = aux_y;
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
