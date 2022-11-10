/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 09:32:42 by almirand          #+#    #+#             */
/*   Updated: 2022/10/14 19:20:40 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
 * Allocate a substring from the given string that starts and ends
 * according to the parameters 'start' and 'len'
 *
 * @param {s} String to substract the substring
 * @param {start} Beginning position of s to substract
 * @param {len} length of the substring
 *
 * @return {substr} Substring from the string s
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (len <= 0 || start >= length)
	{
		substr = (char *)malloc(1 * sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	if (len > length)
		len = length - start;
	substr = malloc (len + 1 * sizeof(*s));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
