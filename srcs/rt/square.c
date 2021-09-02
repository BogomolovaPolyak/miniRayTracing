/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:13:21 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 00:24:27 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_square(t_obj *obj, t_scene *scene, char **splitted)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	if (!square)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Сannot allocate memory", EXIT_FAILURE);
	}
	obj->data = square;
	square->center = split_vectors(splitted[1], scene, splitted);
	square->normal = split_vectors(splitted[2], scene, splitted);
	square->side_size = rt_atof(splitted[3], splitted, scene);
	if (check_normal(&(square->normal)) || square->side_size < 0)
	{
		ft_free_array(splitted);
		ft_exit(scene, "Square parameters are incorrect", EXIT_FAILURE);
	}
	square->normal = vec_norm(square->normal);
	square->side_size = rt_atof(splitted[3], splitted, scene);
	obj->color = split_colors(splitted[4], splitted, scene);
	obj->intersect = &square_intersect;
	obj->normal = &square_normal;
}

t_solved	square_intersect(void *data, t_vec3d view_point, t_vec3d ray_dir)
{
	t_square	*square;
	t_solved	t;
	t_vec3d		from_interpoint_to_center;
	t_vec3d		sq_axis[2];
	double		proj[2];

	square = data;
	sq_axis[0] = vec_mult(square->normal, (t_vec3d){0, 1, 0});
	if (vec_lenth(sq_axis[0]) == 0)
		sq_axis[0] = (t_vec3d){1, 0, 0};
	sq_axis[0] = vec_norm(sq_axis[0]);
	sq_axis[1] = vec_norm(vec_mult(square->normal, sq_axis[0]));
	t = plane_intersect(&(t_plane){square->center, square->normal},
			view_point, ray_dir);
	if (t.t1 != INFINITY)
	{
		from_interpoint_to_center = vec_diff(vec_sum(view_point,
					vec_sc_mult(ray_dir, t.t1)), square->center);
		proj[0] = vec_dot(from_interpoint_to_center, sq_axis[0]);
		proj[1] = vec_dot(from_interpoint_to_center, sq_axis[1]);
		if (fabs(proj[0]) <= square->side_size / 2.
			&& fabs(proj[1]) <= square->side_size / 2.)
			return (t);
	}
	return ((t_solved){INFINITY, INFINITY});
}

t_vec3d	square_normal(void *data, t_vec3d interpoint, t_vec3d ray_dir)
{
	t_square	*sq;

	sq = data;
	vec_norm(interpoint);
	return (turn_normal(sq->normal, ray_dir));
}
