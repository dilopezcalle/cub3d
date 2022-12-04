/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 10:08:09 by almirand          #+#    #+#             */
/*   Updated: 2022/12/04 14:14:31 by almirand         ###   ########.fr       */
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

int	gworldMap[24][24] =
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

int	key_hook(int key, t_window	*wndw)
{
	if (key == W_U)
	{
		if (!gworldMap[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)])
			wndw->pos_x += wndw->dir_x * wndw->spd_move;
		if (!gworldMap[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x])
			wndw->pos_y += wndw->dir_y * wndw->spd_move;
	}
	if (key == S_D)
	{
		if (!gworldMap[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)])
			wndw->pos_x -= wndw->dir_x * wndw->spd_move;
		if (!gworldMap[(int)(wndw->pos_y + wndw->dir_y * \
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
