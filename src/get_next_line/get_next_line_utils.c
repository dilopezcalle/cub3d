/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:20:31 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/10 13:47:07 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	i;

	i = -1;
	str = (void *)malloc(count * size);
	if (str == NULL)
		return (NULL);
	while (++i < (count * size))
		((unsigned char *)str)[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

int	ft_strnl(const char *s)
{
	int	i;
	int	find;

	i = 0;
	if (!s || s[0] == '\0')
		return (-1);
	if ((char)s[0] == '\n')
		return (-2);
	while (s[i] && (char)s[i] != '\n')
	{
		if ((char)s[i] != '\n')
			find = 1;
		i++;
	}
	if (s[i] == '\0')
		return (-1);
	if (find == 1)
		return (++i);
	else
		return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		index;

	if (!s)
		return (NULL);
	if ((int)len == -2)
		len = 1;
	if ((int) start == -2)
		start = 1;
	if (start >= ft_strlen(s) || len <= 0)
		return (NULL);
	index = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)malloc((len + 1) * sizeof(*str));
	if (!str)
		return (NULL);
	while (s[start] && index < len)
	{
		str[index] = s[start];
		index++;
		start++;
	}
	str[index] = '\0';
	return (str);
}
