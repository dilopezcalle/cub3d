/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:27:04 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/10 13:47:41 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// ========== Include ==========

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// ========== Prototypes ==========

char	*get_next_line(int fd);

// ========== Utils ==========

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strnl(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
