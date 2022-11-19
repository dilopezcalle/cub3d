/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:47:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/19 08:12:02 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "structs.h"
#include "libft.h"

void	free_double_str(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
