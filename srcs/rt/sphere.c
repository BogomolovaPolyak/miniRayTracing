/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:05:00 by natali            #+#    #+#             */
/*   Updated: 2021/04/24 20:01:49 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(t_obj *obj, t_scene *scene, char **splitted)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Сannot allocate memory", EXIT_FAILURE);
	}
	obj->data = sphere;
	sphere->radius = rt_atof(splitted[2], splitted, scene) / 2;
	if (sphere->radius < 0)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Sphere diameter cannot be negative", EXIT_FAILURE);
	}
	sphere->center = split_vectors(splitted[1], scene, splitted);
	obj->color = split_colors(splitted[3], splitted, scene);
	obj->intersect = &sphere_intersect;
	obj->normal = &sphere_normal;
}

t_solved	sphere_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir)
{
	t_sphere	*sph;
	t_solved	t;
	t_vec3d		diff;
	double		discr;
	double		values[3];

	sph = data;
	diff = vec_diff(view_point, sph->center);
	values[0] = vec_dot(ray_dir, ray_dir);
	values[1] = 2 * vec_dot(diff, ray_dir);
	values[2] = vec_dot(diff, diff) - sph->radius * sph->radius;
	discr = values[1] * values[1] - 4 * values[0] * values[2];
	if (discr < 0)
		return ((t_solved){INFINITY, INFINITY});
	t.t1 = (-values[1] + sqrtf(discr)) / (2 * values[0]);
	t.t2 = (-values[1] - sqrtf(discr)) / (2 * values[0]);
	return (t);
}

t_vec3d	sphere_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir)
{
	t_sphere	*sph;
	t_vec3d		normal;

	sph = data;
	normal = vec_diff(interpoint, sph->center);
	return (turn_normal(normal, ray_dir));
}
