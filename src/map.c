/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:19:42 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/13 17:17:24 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "utils.h"

static int	check_chars_map(char **map);
static int	check_spaces_map(char **map, int y, int x);

int	check_and_get_map(t_content *content, char **file_content)
{
	char	**map;
	int		i;

	i = 0;
	while (file_content[i])
		i++;
	map = ft_calloc (i + 1, sizeof(char *));
	i = -1;
	while (file_content[++i])
		map[i] = ft_strdup(file_content[i]);
	if (check_chars_map(map))
		return (free_double_str(map), 1);
	content->map = map;
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
