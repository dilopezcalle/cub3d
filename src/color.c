/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:46:07 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/28 18:44:21 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "structs.h"
#include "libft.h"

static int	check_syntax_color(t_color *color, char *str, int start);
static int	save_int_color(t_color *color, char *s_color, int type);
static int	get_int_colors(char *str, t_color *color, int start);
int			minilibx_color(int r, int g, int b);

int	check_and_get_color(t_content *content, char *str)
{
	t_color	*color;
	int		i;

	i = 0;
	color = ft_calloc (1, sizeof(t_color));
	if (!color)
		return (1);
	if ((ft_strncmp(str, "F", 1) == 0 && content->color_floor != -1) || \
		(ft_strncmp(str, "C", 1) == 0 && content->color_ceiling != -1))
		return (printf("Error: Tipo de color repetido\n"), 1);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (printf("Error: Sintaxis de color invalida\n"), 1);
	if (check_syntax_color(color, str, i))
		return (1);
	if (ft_strncmp(str, "F", 1) == 0 && content->color_floor == -1)
		content->color_floor = minilibx_color(color->r, color->g, color->b);
	else if (ft_strncmp(str, "C", 1) == 0 && content->color_ceiling == -1)
		content->color_ceiling = minilibx_color(color->r, color->g, color->b);
	else
		return (free(color), 1);
	return (free(color), 0);
}

static int	check_syntax_color(t_color *color, char *str, int start)
{
	char	*rgb;
	int		i;

	i = start;
	rgb = ft_strtrim(str, " ");
	while (rgb[i] && rgb[i] != ' ')
		i++;
	if (rgb[i])
		return (free(rgb), printf("Error: Argumentos de color invalidos\n"), 1);
	color->r = -1;
	color->g = -1;
	color->b = -1;
	if (get_int_colors(rgb, color, start))
		return (free(rgb), free(color), 1);
	free(rgb);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		return (free(color), 1);
	return (0);
}

static int	get_int_colors(char *str, t_color *color, int start)
{
	char	*s_color;
	int		type;
	int		i;

	type = 1;
	i = start;
	while (str[i])
	{
		while (str[i] && str[i] != ',')
			i++;
		s_color = ft_substr(str, start, i - start);
		if (!s_color)
			return (1);
		if (str[i] && str[i] == ',' && !str[i + 1])
			return (free(s_color), 0);
		if (str[i])
			i++;
		start = i;
		if (save_int_color(color, s_color, type))
			return (free(s_color), 1);
		free(s_color);
		type++;
	}
	return (0);
}

static int	save_int_color(t_color *color, char *s_color, int type)
{
	int	i;

	i = 0;
	while (s_color[i])
	{
		if (!ft_isdigit(s_color[i]))
			return (printf("Error: Caracter de color invalido\n"), 1);
		i++;
	}
	if (type <= 3 && ((ft_atoi(s_color) > 0 && ft_atoi(s_color) <= 255) \
		|| (ft_atoi(s_color) == 0 && s_color[0] == '0')))
	{
		if (type == 1)
			color->r = ft_atoi(s_color);
		if (type == 2)
			color->g = ft_atoi(s_color);
		if (type == 3)
			color->b = ft_atoi(s_color);
	}
	else
		return (1);
	return (0);
}

int	minilibx_color(int r, int g, int b)
{
	return (100 << 24 | r << 16 | g << 8 | b);
}
