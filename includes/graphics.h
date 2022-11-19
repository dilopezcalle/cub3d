/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:50:04 by almirand          #+#    #+#             */
/*   Updated: 2022/11/19 09:51:29 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

/* Data about image
 *
 * img		- Image ID
 * addr		- image
 * bits_pix	- Depth of image
 * len_line	- Num of bytes to store an image line
 * endian	- little or big endian
 * */
typedef struct s_img {
	void			*image;
	int				*addr;
	int				bpp;
	int				size;
	int				endian;
}				t_img;

#endif
