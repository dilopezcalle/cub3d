/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:31:58 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/19 15:25:54 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "libft.h"
#include "syntax.h"
#include "utils.h"

static char	*get_str_file(int fd);

char		*get_next_line(int fd);

t_content	*parser(char *file)
{
	int			fd;
	char		*str;
	t_content	*content;

	if (check_extension(file, ".cub"))
		return (printf("Error: El fichero no acaba en .cub\n"), NULL);
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
		return (printf("Error: No se pudo crear la estructura\n"), NULL);
	return (content);
}

static char	*get_str_file(int fd)
{
	char	*line;
	char	*str;
	char	*aux;

	line = get_next_line(fd);
	if (!line)
		return (printf("Error: El fichero no existe o esta vacío\n"), line);
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
