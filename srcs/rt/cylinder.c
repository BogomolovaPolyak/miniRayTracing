/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:22:50 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 00:24:46 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_cylinder(t_obj *obj, t_scene *scene, char **splitted)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Cannot allocate memory", EXIT_FAILURE);
	}
	obj->data = cylinder;
	cylinder->normal = split_vectors(splitted[2], scene, splitted);
	cylinder->radius = rt_atof(splitted[3], splitted, scene) / 2;
	cylinder->height = rt_atof(splitted[4], splitted, scene);
	if (check_normal(&(cylinder->normal))
		|| cylinder->radius < 0 || cylinder->height < 0)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Cylinder parameters are incorrect", EXIT_FAILURE);
	}
	cylinder->normal = vec_norm(cylinder->normal);
	cylinder->coord = split_vectors(splitted[1], scene, splitted);
	cylinder->bottom = vec_sum(cylinder->coord,
			vec_sc_mult(cylinder->normal, cylinder->height));
	obj->color = split_colors(splitted[5], splitted, scene);
	obj->intersect = &cylinder_intersect;
	obj->normal = &cylinder_normal;
}

t_solved	check_cyl(t_solved t, t_cylinder *cyl,
				t_vec3d diff, t_vec3d ray_dir)
{
	t_solved	check;

	check.t1 = vec_dot(ray_dir, cyl->normal) * t.t1
		+ vec_dot(diff, cyl->normal);
	check.t2 = vec_dot(ray_dir, cyl->normal) * t.t2
		+ vec_dot(diff, cyl->normal);
	if (check.t1 < 0 || check.t1 > cyl->height)
		t.t1 = INFINITY;
	if (check.t2 < 0 || check.t2 > cyl->height)
		t.t2 = INFINITY;
	return (t);
}

t_solved	cylinder_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir)
{
	t_cylinder	*cyl;
	t_solved	t;
	t_vec3d		diff;
	double		values[3];
	double		discr;

	cyl = data;
	diff = vec_diff(view_point, cyl->coord);
	values[0] = vec_dot(ray_dir, ray_dir)
		- powf(vec_dot(ray_dir, cyl->normal), 2);
	values[1] = (vec_dot(ray_dir, diff)
			- vec_dot(ray_dir, cyl->normal) * vec_dot(diff, cyl->normal)) * 2;
	values[2] = vec_dot(diff, diff) - powf(vec_dot(diff, cyl->normal), 2)
		- powf(cyl->radius, 2);
	discr = values[1] * values[1] - 4 * values[0] * values[2];
	if (discr < -0.00001)
		return ((t_solved){INFINITY, INFINITY});
	t.t1 = (-values[1] + sqrtf(discr)) / (2 * values[0]);
	t.t2 = (-values[1] - sqrtf(discr)) / (2 * values[0]);
	t = check_cyl(t, cyl, diff, ray_dir);
	return (t);
}

t_vec3d	cylinder_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir)
{
	t_cylinder	*cy;
	t_vec3d		sum;
	double		t;

	cy = data;
	t = vec_dot(vec_diff(interpoint, cy->bottom), cy->normal);
	sum = vec_sum(cy->bottom, vec_sc_mult(cy->normal, t));
	return (turn_normal(vec_diff(interpoint, sum), ray_dir));
}
