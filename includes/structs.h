/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:11:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/12/08 12:51:54 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIDTH 1280
# define HEIGHT 768
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
 * spd_move		- Movement speed
 * cam_speed	- Camera speed
 * texture		- Saved textures pixl per pixel
 * content		- Content structure
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
	int				**buff;
	double			spd_move;
	double			spd_cam;
	int				**texture;
	t_content		*content;
	double			aux_dirx;
	double			aux_planex;
	int				map_weight;
	int				map_height;
	int				front;
	int				back;
	int				right;
	int				cam_right;
	int				cam_left;
	int				left;
	int				exit;
	double			aux_x;
	double			aux_y;
}			t_window;

/*
 * stepx			- Direction to step in x (+1, -1)
 * stepy			- Direction to step in y (+1, -1)
 * cam_x			- X position of cam
 * xdir				- ray direction X
 * ydir				- ray direction Y
 * posx				- Player X pos int
 * posy				- Player Y pos int
 * delta_x			- Dist from x to next x
 * delta_y			- Dist from y to next y
 * perp_wall_dist	- Perp distance from player to wall
 * raydist_x		- side dist ray from pos to next x
 * raydist_y		- side dist ray from pos to next y
 * hit				- If there's a wall hit
 * side				- 0 NS, 1 SW
 * draw_start		- Lowest pixel to fill
 * draw_end			- Highest pixel to fill
 * line_height		- Height of line to draw
 * wall_x			- value of wall in x
 * tex_x			- Value coord x of texture
 * tex_pos			- Starting texture coord
 * tex_y			- Value coord y of texture
 */
typedef struct s_maths
{
	float	stepx;
	float	stepy;
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
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}			t_maths;

#endif
