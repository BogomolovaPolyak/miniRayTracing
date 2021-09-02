/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:05:16 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/26 15:11:30 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	choose_t(t_solved t, t_range range)
{
	if (t.t1 > range.min && t.t1 < range.max)
	{
		if (t.t2 > range.min && t.t2 < range.max)
		{
			if (t.t1 < t.t2)
				return (t.t1);
			return (t.t2);
		}
		return (t.t1);
	}
	if (t.t2 > range.min && t.t2 < range.max)
		return (t.t2);
	return (INFINITY);
}

t_closest	find_closest(t_obj *obj, t_vec3d view_point,
						t_vec3d ray_dir, t_range range)
{
	t_closest	res;
	t_solved	dist;
	double		t;

	res.t = INFINITY;
	while (obj)
	{
		dist = obj->intersect(obj->data, view_point, ray_dir);
		t = choose_t(dist, range);
		if (t != INFINITY && t < res.t)
		{
			res.dist = dist;
			res.t = t;
			res.inter = vec_sum(view_point, vec_sc_mult(ray_dir, res.t));
			res.normal = obj->normal(obj->data, res.inter, ray_dir);
			res.color = obj->color;
		}
		obj = obj->next;
	}
	return (res);
}

void	drawing_image(t_scene *sc, t_vec3d ray_dir, int x, int y)
{
	t_closest	cl;

	cl = find_closest(sc->obj, sc->camera->view_point,
			ray_dir, (t_range){1, INFINITY});
	if (cl.t != INFINITY)
	{
		cl.color = calc_light(sc->ambient, cl, sc->light, sc->obj);
		my_mlx_pixel_put(&sc->img, x, y,
			create_rgb(cl.color.R, cl.color.G, cl.color.B));
	}
	else
		my_mlx_pixel_put(&sc->img, x, y, create_rgb(0, 0, 0));
}

t_vec3d	create_ray(int x, int y, t_camera *c)
{
	t_vec3d	ray;

	ray.x = (double)x * c->canvas.x_pixel;
	ray.y = (double)y * c->canvas.y_pixel;
	ray.z = 1;
	return (ray);
}

void	create_canvas(t_scene *sc, int save)
{
	t_matrix	matrix;
	t_vec3d		ray;
	int			x;
	int			y;

	matrix = look_at(sc->camera->view_point, sc->camera->normal);
	y = sc->height / 2;
	while (y > sc->height / (-2))
	{
		x = sc->width / (-2);
		while (x < sc->width / 2)
		{
			ray = create_ray(x, y, sc->camera);
			ray = matrix_mult(ray, matrix);
			ray = vec_diff(ray, sc->camera->view_point);
			drawing_image(sc, vec_norm(ray), x + sc->width / 2,
				abs(y - sc->height / 2));
			x++;
		}
		y--;
	}
	if (save)
		image_to_bmp(sc);
	else
		mlx_put_image_to_window(sc->init, sc->win, sc->img.img, 0, 0);
}
