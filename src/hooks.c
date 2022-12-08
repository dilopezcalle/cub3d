/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 10:08:09 by almirand          #+#    #+#             */
/*   Updated: 2022/12/08 14:41:16 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "keys.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "minilibx/mlx.h"

int	key_hook1(t_window *wndw, char	**map);
int	key_hook2(t_window	*wndw, char **map);
int	key_hook3(t_window	*wndw);
int	exit_free_wndw(t_window *wndw);

int	key_press(int key, t_window *wndw)
{
	if (key == W_U)
		wndw->front = 1;
	else if (key == S_D)
		wndw->back = 1;
	else if (key == A_L)
		wndw->left = 1;
	else if (key == D_R)
		wndw->right = 1;
	else if (key == AR_L)
		wndw->cam_left = 1;
	else if (key == AR_R)
		wndw->cam_right = 1;
	else if (key == ESC)
		wndw->exit = 1;
	return (1);
}

int	key_release(int key, t_window *wndw)
{
	if (key == W_U)
		wndw->front = 0;
	else if (key == S_D)
		wndw->back = 0;
	else if (key == A_L)
		wndw->left = 0;
	else if (key == D_R)
		wndw->right = 0;
	else if (key == ESC)
		wndw->exit = 0;
	else if (key == AR_L)
		wndw->cam_left = 0;
	else if (key == AR_R)
		wndw->cam_right = 0;
	return (1);
}

int	key_hook(t_window	*wndw)
{
	char	**map;

	wndw->aux_x = wndw->pos_x;
	wndw->aux_y = wndw->pos_y;
	map = wndw->content->map;
	if (wndw->front == 1)
	{
		if ((map[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_x * wndw->spd_move)]) == '0')
			wndw->pos_x += wndw->dir_x * wndw->spd_move;
		if ((map[(int)(wndw->pos_y + wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y += wndw->dir_y * wndw->spd_move;
	}
	if (wndw->back == 1)
	{
		if ((map[(int)(wndw->pos_y)][(int)(wndw->pos_x - \
				wndw->dir_x * wndw->spd_move)]) == '0')
			wndw->pos_x -= wndw->dir_x * wndw->spd_move;
		if ((map[(int)(wndw->pos_y - wndw->dir_y * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y -= wndw->dir_y * wndw->spd_move;
	}
	return (key_hook1(wndw, map));
}

int	key_hook1(t_window *wndw, char	**map)
{
	if (wndw->right == 1)
	{
		if ((map[(int)(wndw->pos_y)][(int)(wndw->pos_x - \
				wndw->dir_y * wndw->spd_move)]) == '0')
			wndw->pos_x -= wndw->dir_y * wndw->spd_move;
		if ((map[(int)(wndw->pos_y + wndw->dir_x * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y -= -wndw->dir_x * wndw->spd_move;
	}
	if (wndw->left == 1)
	{
		if ((map[(int)(wndw->pos_y)][(int)(wndw->pos_x + \
				wndw->dir_y * wndw->spd_move)]) == '0')
			wndw->pos_x += wndw->dir_y * wndw->spd_move;
		if ((map[(int)(wndw->pos_y - wndw->dir_x * \
				wndw->spd_move)][(int)wndw->pos_x]) == '0')
			wndw->pos_y += -wndw->dir_x * wndw->spd_move;
	}
	return (key_hook2(wndw, map));
}

int	key_hook2(t_window	*wndw, char	**map)
{
	if (map[(int)(wndw->pos_y)][(int)(wndw->pos_x + wndw->dir_x * \
	wndw->spd_move)] == '1' && map[(int)(wndw->pos_y + wndw->dir_y * \
	wndw->spd_move)][(int)wndw->pos_x] == '1')
	{
		wndw->pos_x = wndw->aux_x;
		wndw->pos_y = wndw->aux_y;
	}
	if (wndw->cam_left == 1)
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
	return (key_hook3(wndw));
}
