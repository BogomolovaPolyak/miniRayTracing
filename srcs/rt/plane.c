/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:59:33 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 00:24:08 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(t_obj *obj, t_scene *scene, char **splitted)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Сannot allocate memory", EXIT_FAILURE);
	}
	obj->data = plane;
	plane->coord = split_vectors(splitted[1], scene, splitted);
	plane->normal = split_vectors(splitted[2], scene, splitted);
	if (check_normal(&(plane->normal)))
	{
		ft_free_array(splitted);
		ft_exit(scene, "Norm normal should be in range [-1,1]", EXIT_FAILURE);
	}
	plane->normal = vec_norm(plane->normal);
	obj->color = split_colors(splitted[3], splitted, scene);
	obj->intersect = &plane_intersect;
	obj->normal = &plane_normal;
}

t_solved	plane_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir)
{
	t_plane		*plane;
	t_solved	t;
	double		denom;

	plane = data;
	denom = vec_dot(plane->normal, ray_dir);
	if (fabs(denom) > 0.00001)
	{
		t.t1 = vec_dot(vec_diff(plane->coord, view_point),
				plane->normal) / denom;
		if (t.t1 >= 0)
			return ((t_solved){t.t1, INFINITY});
	}
	return ((t_solved){INFINITY, INFINITY});
}

t_vec3d	plane_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir)
{
	t_plane	*plane;

	plane = data;
	vec_norm(interpoint);
	return (turn_normal(plane->normal, ray_dir));
}
