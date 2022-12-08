/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:39:02 by almirand          #+#    #+#             */
/*   Updated: 2022/12/08 10:35:37 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

int		free_content_struct(t_content *content);

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
		if ((int)((wndw->content->map)[math->posy][math->posx]) - '0' > 0)
			math->hit = 1;
	}
	if (!math->side)
		math->perp_wall_dist = (math->raydist_x - math->delta_x);
	else
		math->perp_wall_dist = (math->raydist_y - math->delta_y);
}

int	init_hook(t_window *wndw)
{
	wndw->front = 0;
	wndw->back = 0;
	wndw->left = 0;
	wndw->right = 0;
	wndw->exit = 0;
	return (1);
}

int	exit_free_wndw(t_window *wndw)
{
	free_content_struct(wndw->content);
	exit (0);
}
