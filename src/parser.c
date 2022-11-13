/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:31:58 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/13 17:15:16 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "libft.h"
#include "syntax.h"
#include "utils.h"

static int	check_arg_syntax(char *file);
static char	*get_str_file(int fd);

char		*get_next_line(int fd);

t_content	*parser(char *file)
{
	int			fd;
	char		*str;
	t_content	*content;

	if (check_arg_syntax(file))
		return (printf("El fichero no acaba en .cub"), NULL);
	fd = open (file, O_RDONLY);
	if (fd == -1 && close(fd) == 0)
		return (perror("Error:"), NULL);
	str = get_str_file(fd);
	if (!str)
		return (0);
	if (check_str_nl(str))
		return (0);
	content = ft_calloc(1, sizeof(t_content));
	if (!content)
		return (free(str), NULL);
	if (get_content_struct(content, str))
		return (printf("Error al crear la estructura\n"), NULL);
	fd = 0;
	while (content->map[fd])
	{
		printf("%s\n", content->map[fd]);
		fd++;
	}
	free_content_struct(content);
	return (content);
}

static int	check_arg_syntax(char *file)
{
	int		i;
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		return (1);
	return (0);
}

static char	*get_str_file(int fd)
{
	char	*line;
	char	*str;
	char	*aux;

	line = get_next_line(fd);
	if (!line)
		return (printf("Error: Fichero vacío\n"), line);
	str = 0;
	str = ft_strjoin(line, "");
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		aux = ft_strdup(str);
		free(str);
		str = ft_strjoin(aux, line);
		free(aux);
		free(line);
		line = get_next_line(fd);
	}
	return (str);
}
