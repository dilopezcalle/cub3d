/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:31:58 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/10 16:18:49 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "libft.h"

static int	check_arg_syntax(char *file);
static char	**get_str_file(int fd);

char		*get_next_line(int fd);

int	parser(char *file)
{
	int		i = 0;
	int		fd;
	char	**content;

	if (check_arg_syntax(file))
		return (1);
	fd = open (file, O_RDONLY);
	if (fd == -1 && close(fd) == 0)
		return (perror("Error"), 1);
	content = get_str_file(fd);
	while (content[i])
	{
		printf("%s\n", content[i]);
		i++;
	}
	return (0);
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

static char	**get_str_file(int fd)
{
	char	*line;
	char	*str;
	char	*aux;
	char	**content;

	line = get_next_line(fd);
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
		line = get_next_line(fd);in
	}
	content = ft_split(str, '\n');
	free(str);
	return (content);
}
