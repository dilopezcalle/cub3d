/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:31:02 by almirand          #+#    #+#             */
/*   Updated: 2022/10/07 08:48:04 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Allocates sufficient momery for a copy of s1,
 * copies it and returns its pointer.
 *
 * @param {s1} String to copy
 *
 * @return {str} Copy of the string after memory being allocated
 */
char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	length;

	length = ft_strlen(s1) + 1;
	if (s1[0] == '\0')
	{
		str = (char *)ft_calloc(2, sizeof(char));
		return (str);
	}
	str = malloc (sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, length);
	return (str);
}
