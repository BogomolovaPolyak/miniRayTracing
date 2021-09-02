/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:46:32 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 00:21:04 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_TAB 48

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

typedef struct s_matrix
{
	double	m[4][4];
}	t_matrix;

typedef struct s_color
{
	int	R;
	int	G;
	int	B;
}	t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	t_color	intense;
}	t_ambient;

typedef struct s_canvas
{
	double	width;
	double	x_pixel;
	double	y_pixel;
}	t_canvas;

typedef struct s_camera
{
	t_vec3d			view_point;
	t_vec3d			normal;
	int				FOV;
	t_canvas		canvas;
	struct s_camera	*next;
	struct s_camera	*prev;
}	t_camera;

typedef struct s_light
{
	t_vec3d			point;
	double			br;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	t_vec3d		center;
	double		radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3d		coord;
	t_vec3d		normal;
}	t_plane;

typedef struct s_square
{
	t_vec3d			center;
	t_vec3d			normal;
	double			side_size;
}	t_square;

typedef struct s_cylinder
{
	t_vec3d			coord;
	t_vec3d			normal;
	double			radius;
	double			height;
	t_vec3d			bottom;
}	t_cylinder;

typedef struct s_triangle
{
	t_vec3d		coord0;
	t_vec3d		coord1;
	t_vec3d		coord2;
	t_vec3d		normal;
	t_plane		plane;
}	t_triangle;

typedef struct s_solved
{
	double	t1;
	double	t2;
}	t_solved;

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

typedef struct s_obj
{
	void			*data;
	t_solved		(*intersect)(void *d, t_vec3d v_p, t_vec3d dir);
	t_vec3d			(*normal)(void *d, t_vec3d i_p, t_vec3d dir);
	double			t_min;
	double			t_max;
	t_color			color;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	int			width;
	int			height;
	t_ambient	ambient;
	t_camera	*camera;
	t_light		*light;
	t_obj		*obj;
	void		*init;
	void		*win;
	t_data		img;
}	t_scene;

typedef struct s_closest
{
	t_solved	dist;
	double		t;
	t_vec3d		inter;
	t_vec3d		normal;
	t_color		color;
}	t_closest;

/*
** vectors utils
*/
t_vec3d		vec_sum(t_vec3d vec1, t_vec3d vec2);
t_vec3d		vec_diff(t_vec3d vec1, t_vec3d vec2);
double		vec_lenth(t_vec3d vec);
double		vec_dist(t_vec3d vec1, t_vec3d vec2);
double		vec_dot(t_vec3d vec1, t_vec3d vec2);
t_vec3d		vec_sc_mult(t_vec3d vec, double scalar);
t_vec3d		vec_mult(t_vec3d vec1, t_vec3d vec2);
t_vec3d		vec_norm(t_vec3d ray);
t_vec3d		turn_normal(t_vec3d normal, t_vec3d ray_dir);

/*
** parser
*/
int			rt_atoi(char *str, char **spl, t_scene *scene);
double		rt_atof(char *str, char **spl, t_scene *scene);
char		**rt_split_set(char *str, char *set, t_scene *scene);
t_vec3d		split_vectors(char *line, t_scene *scene, char **array);
t_color		split_colors(char *line, char **array, t_scene *scene);
int			check_normal(t_vec3d *normal);
int			arr_len(char **array);
void		parse_scene(int fd, t_scene *scene);
void		parse_c(char **spl, t_scene *scene);
void		calc_cam(t_camera *cam, int width, int height);
void		parse_l(char **spl, t_scene *scene);
void		parse_obj(char **splitted, t_scene *scene);
void		parse_sphere(t_obj *obj, t_scene *scene, char **splitted);
void		parse_plane(t_obj *obj, t_scene *scene, char **splitted);
void		parse_square(t_obj *obj, t_scene *scene, char **splitted);
void		parse_cylinder(t_obj *obj, t_scene *scene, char **splitted);
void		parse_triangle(t_obj *obj, t_scene *scene, char **splitted);

/*
** mlx utils
*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_win(t_scene *scene, int save);
int			press_key(int key_code, t_scene *sc);
int			red_cross(t_scene *scene);
void		image_to_bmp(t_scene *sc);

/*
** colors utils
*/
int			create_rgb(int r, int g, int b);
t_color		color_mix(t_color c1, t_color c2);
t_color		color_sum(t_color c1, t_color c2);
t_color		light_bright(t_color color, double bright);
void		check_color(t_color *res);

/*
** other utils
*/
t_scene		*new_scene(void);
void		free_scene(t_scene *scene);
void		ft_exit(t_scene *scene, char *message, int status);

/*
** raytracing
*/
t_vec3d		matrix_mult(t_vec3d vec, t_matrix mtrx);
t_matrix	look_at(t_vec3d view_point, t_vec3d dir);
void		create_canvas(t_scene *scene, int save);
t_closest	find_closest(t_obj *obj, t_vec3d view_point,
				t_vec3d ray_dir, t_range range);
t_color		calc_light(t_ambient amb, t_closest cl, t_light *light, t_obj *obj);
t_vec3d		sphere_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir);
t_solved	sphere_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir);
t_vec3d		plane_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir);
t_solved	plane_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir);
t_vec3d		square_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir);
t_solved	square_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir);
t_vec3d		triangle_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir);
t_solved	triangle_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir);
t_vec3d		cylinder_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir);
t_solved	cylinder_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir);

#endif
