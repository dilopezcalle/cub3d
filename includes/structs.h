/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:11:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/19 14:03:27 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIDTH 640
# define HEIGHT 480
# define TEX_SIZE 64

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_content
{
	char	**map;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		color_floor;
	int		color_ceiling;
}			t_content;

/* Data about image
 *
 * img		- Image ID
 * addr		- image
 * bits_pix	- Depth of image
 * size		- size of image
 * endian	- little or big endian
 * */
typedef struct s_img {
	void			*image;
	int				*addr;
	int				bpp;
	int				size;
	int				endian;
	int				width;
	int				height;
}				t_img;

/* Window data
 * mlx			- Connection ID
 * win			- Window ID
 * img			- Image
 * posX			- Player X position
 * posY			- Player Y position
 * dirX			- Camera X position
 * dirY			- Camera Y position
 * buff			- Buffer
 */
typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_img	img;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		**buff;
	int		full_buff;
	double	spd_move;
	double	spd_cam;
	int		**texture;
}			t_window;

#endif
