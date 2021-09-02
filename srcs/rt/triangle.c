/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:17:50 by natali            #+#    #+#             */
/*   Updated: 2021/04/25 06:58:16 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_triangle(t_obj *obj, t_scene *scene, char **splitted)
{
	t_triangle	*tr;

	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (!tr)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Cannot allocate memory", EXIT_FAILURE);
	}
	obj->data = tr;
	tr->coord0 = split_vectors(splitted[1], scene, splitted);
	tr->coord1 = split_vectors(splitted[2], scene, splitted);
	tr->coord2 = split_vectors(splitted[3], scene, splitted);
	tr->normal = vec_norm(vec_mult(vec_diff(tr->coord1,
					tr->coord0), vec_diff(tr->coord2, tr->coord0)));
	tr->plane.coord = tr->coord0;
	tr->plane.normal = tr->normal;
	obj->color = split_colors(splitted[4], splitted, scene);
	obj->intersect = &triangle_intersect;
	obj->normal = &triangle_normal;
}

int	tr_check(t_triangle *tr, t_vec3d interpoint, t_vec3d normal)
{
	t_vec3d	tmp;

	tmp = vec_mult(vec_diff(tr->coord1, tr->coord0),
			vec_diff(interpoint, tr->coord0));
	if (vec_dot(normal, tmp) < -0.00001)
		return (0);
	tmp = vec_mult(vec_diff(tr->coord2, tr->coord1),
			vec_diff(interpoint, tr->coord1));
	if (vec_dot(normal, tmp) < -0.00001)
		return (0);
	tmp = vec_mult(vec_diff(tr->coord0, tr->coord2),
			vec_diff(interpoint, tr->coord2));
	if (vec_dot(normal, tmp) < -0.00001)
		return (0);
	return (1);
}

t_solved	triangle_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir)
{
	t_triangle	*tr;
	t_solved	t;
	t_vec3d		tmp;

	tr = data;
	tr->plane.normal = turn_normal(tr->normal, ray_dir);
	t = plane_intersect(&(tr->plane), view_point, ray_dir);
	tmp = vec_sum(view_point, vec_sc_mult(ray_dir, t.t1));
	if (t.t1 < INFINITY && tr_check(tr, tmp, tr->normal))
		return ((t_solved){t.t1, INFINITY});
	return ((t_solved){INFINITY, INFINITY});
}

t_vec3d	triangle_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir)
{
	t_triangle	*tr;

	tr = data;
	vec_norm(interpoint);
	return (turn_normal(tr->normal, ray_dir));
}
