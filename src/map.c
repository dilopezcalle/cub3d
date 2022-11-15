/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:19:42 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/15 09:16:27 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "utils.h"

static int	check_chars_map(char **map);
static int	get_max_width_map(char **map);
static int	check_spaces_map(char **map, int y, int x);

int	check_and_get_map(t_content *content, char **file_content)
{
	static int	y;
	int			x;
	int			max_width;

	while (file_content[y])
		y++;
	content->map = ft_calloc (y + 1, sizeof(char *));
	if (!content->map)
		return (1);
	max_width = get_max_width_map(file_content);
	y = -1;
	while (file_content[++y])
	{
		x = -1;
		content->map[y] = ft_calloc(max_width + 1, sizeof(char));
		if (!content->map[y])
			return (1);
		while (file_content[y][++x])
			content->map[y][x] = file_content[y][x];
		while (x < max_width)
			content->map[y][x++] = ' ';
	}
	if (check_chars_map(content->map))
		return (1);
	return (0);
}

static int	check_chars_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != '0' && \
				map[y][x] != '1' && map[y][x] != 'N' && \
				map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W')
				return (printf("Error: Caracter en mapa invalido\n"), 1);
			else if (map[y][x] != '1' && map[y][x] != ' ' \
					&& check_spaces_map(map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	check_spaces_map(char **map, int y, int x)
{
	int	i;
	int	len;

	len = 0;
	while (map[len])
		len++;
	if (y == 0 || y == len - 1)
		return (printf("Error: Mapa sin cerrar lineas extremos y\n"), 1);
	len = 0;
	while (map[y][len])
		len++;
	if (x == 0 || x == len - 1)
		return (printf("Error: Mapa sin cerrar lineas extremos x\n"), 1);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || \
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (printf("Error: Mapa sin cerrar\n"), 1);
	return (0);
}

static int	get_max_width_map(char **map)
{
	int	y;
	int	max_width;

	y = 0;
	max_width = -1;
	while (map[y])
	{
		if ((int)ft_strlen(map[y]) > max_width)
			max_width = ft_strlen(map[y]);
		y++;
	}
	return (max_width);
}
