/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:47:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/12/08 11:40:09 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "structs.h"
#include "libft.h"

int	free_double_str(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (-1);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (-1);
}

int	free_content_struct(t_content *content)
{
	if (!content)
		return (0);
	free_double_str(content->map);
	if (content->path_no)
		free(content->path_no);
	if (content->path_so)
		free(content->path_so);
	if (content->path_we)
		free(content->path_we);
	if (content->path_ea)
		free(content->path_ea);
	free(content);
	return (0);
}

int	check_extension(char *file, char *set)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strncmp(extension, set, ft_strlen(set) + 1) != 0)
		return (1);
	return (0);
}

void	clean_buffer(t_window *wndw)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			wndw->buff[y][x] = 0;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
