/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:11:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/10 11:30:44 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_color
{
	int	R;
	int	G;
	int	B;
}			t_color;

typedef struct s_map
{
	char	**map;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	long	color_floor;
	long	color_ceiling;
}			t_map;

#endif