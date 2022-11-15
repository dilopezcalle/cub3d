/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:33:25 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/15 09:59:55 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "structs.h"
#include "libft.h"
#include "utils.h"
#include "color.h"
#include "map.h"

static int	save_access_texture(t_content *content, char *str, int i);
static int	get_path_file(t_content *content, char *str);
static int	get_type_data(char **str, int i);

int	check_str_nl(char *str)
{
	int	i;
	int	num_lines;

	i = -1;
	num_lines = 0;
	while (str[++i] && num_lines < 6)
	{
		if (str[i] == '\n')
			continue ;
		while (str[i] && str[i] != '\n')
			i++;
		num_lines++;
	}
	while (str[i] && str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] == '\n')
			return (printf("Error: Formato de mapa invalido"), 1);
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i])
			i++;
	}
	return (0);
}

int	get_content_struct(t_content *content, char *str)
{
	char		**file_content;
	int			type;
	int			i;

	i = -1;
	file_content = ft_split(str, '\n');
	if (!file_content)
		return (free_content_struct(content), free(str), 1);
	content->color_floor = -1;
	content->color_ceiling = -1;
	while (file_content[++i])
	{
		type = get_type_data(file_content, i);
		if ((type == 1 && get_path_file(content, file_content[i])) || type == 0 \
			|| (type == 2 && check_and_get_color(content, file_content[i])) \
			|| (type == 3 && check_and_get_map(content, file_content + i)))
			return (free(str), free_double_str(file_content), \
			free_content_struct(content), printf("Error: Datos invalidos\n"), 1);
		else if (type == 3)
			break ;
	}
	if (i < 6 || !file_content[i])
		return (printf("Error: Faltan datos en el fichero\n"), free(str), \
		free_double_str(file_content), free_content_struct(content), 1);
	return (free(str), free_double_str(file_content), 0);
}

// 0: No corresponde a ninguna opcion. 1: Textura de un muro. 2. Mapa
static int	get_type_data(char **str, int i)
{
	if (ft_strncmp(str[i], "NO ", 3) == 0 || \
		ft_strncmp(str[i], "SO ", 3) == 0 || \
		ft_strncmp(str[i], "EA ", 3) == 0 || \
		ft_strncmp(str[i], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(str[i], "F ", 2) == 0 || \
		ft_strncmp(str[i], "C ", 2) == 0)
		return (2);
	if (i == 6)
		return (3);
	return (0);
}

static int	get_path_file(t_content *content, char *str)
{
	int	i;

	if ((ft_strncmp(str, "NO ", 3) == 0 && content->path_no) || \
		(ft_strncmp(str, "SO ", 3) == 0 && content->path_so) || \
		(ft_strncmp(str, "EA ", 3) == 0 && content->path_ea) || \
		(ft_strncmp(str, "WE ", 3) == 0 && content->path_we))
		return (printf("Error: Tipo de textura repetida\n"), 1);
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
		return (printf("Error: Sintaxis de textura invalida1\n"), 1);
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (printf("Error: Sintaxis de textura invalida2\n"), 1);
	if (save_access_texture(content, str, i))
		return (1);
	return (0);
}

static int	save_access_texture(t_content *content, char *str, int i)
{
	int		fd;
	char	*file;

	file = ft_strtrim(str + i, " ");
	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(file), perror("Error"), 1);
	close(fd);
	if (ft_strncmp(str, "NO", 2) == 0 && !content->path_no)
		content->path_no = file;
	else if (ft_strncmp(str, "SO", 2) == 0 && !content->path_so)
		content->path_so = file;
	else if (ft_strncmp(str, "EA", 2) == 0 && !content->path_ea)
		content->path_ea = file;
	else if (ft_strncmp(str, "WE", 2) == 0 && !content->path_we)
		content->path_we = file;
	else
		return (free(file), printf("Error: Cara de textura repetida\n"), 1);
	return (0);
}
