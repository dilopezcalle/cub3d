/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:11:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/11/26 17:44:42 by almirand         ###   ########.fr       */
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
	unsigned char	*addr;
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
	void			*mlx;
	void			*win;
	t_img			img;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	unsigned char	**buff;
	int				full_buff;
	double			spd_move;
	double			spd_cam;
	unsigned char	**texture;
	t_content		*content;
	double			aux_dirx;
	double			aux_planex;
}			t_window;

/*
 * xdir_left		- Direction for ray on left, x = 0
 * ydir_left		- Direction for ray on left, y = 0
 * xdir_right		- Direction for ray on right, x = width
 * ydir_right		- Direction for ray on right, y = width
 * y_screen			- Horizon y compared to center of screen
 * cam_z			- Camera vertical position, being 0.5 middle of the screen.
 * row_dist			- Distance from camera to floor of each row
 * leftx_colum		- X coord of left column
 * lefty_colum		- Y coord of left column
 * stepx			- Direction to step in x (+1, -1)
 * stepy			- Direction to step in y (+1, -1)
 * text_x			- Coordinate x of texture
 * text_y			- Coordinate y of texture
 * cam_x			- X position of cam
 * xdir				- Camera X pos
 * ydir				- Camera Y pos
 * posx				- Player X pos int
 * posy				- Player Y pos int
 * delta_x			- Dist from x to next x
 * delta_y			- Dist from y to next y
 * perp_wall_dist	- Perp distance from player to wall
 * raydist_x		- Length ray from pos to next x
 * raydist_y		- Length ray from pos to next y
 * hit				- If there's a wall hit
 * side				- 0 NS, 1 SW
 */
typedef struct s_maths
{
	float	xdir_left;
	float	xdir_right;
	float	ydir_left;
	float	ydir_right;
	float	y_screen;
	float	cam_z;
	float	row_dist;
	float	leftx_column;
	float	lefty_column;
	float	stepx;
	float	stepy;
	float	text_x;
	float	text_y;
	double	cam_x;
	double	xdir;
	double	ydir;
	int		posx;
	int		posy;
	double	delta_x;
	double	delta_y;
	double	perp_wall_dist;
	double	raydist_x;
	double	raydist_y;
	int		hit;
	int		side;
}			t_maths;

#endif
