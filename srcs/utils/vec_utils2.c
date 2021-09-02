/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 22:07:44 by natali            #+#    #+#             */
/*   Updated: 2021/04/20 22:08:29 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_dot(t_vec3d vec1, t_vec3d vec2)
{
	double	scalar;

	scalar = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (scalar);
}

t_vec3d	vec_sc_mult(t_vec3d vec, double scalar)
{
	t_vec3d	res;

	res.x = vec.x * scalar;
	res.y = vec.y * scalar;
	res.z = vec.z * scalar;
	return (res);
}

t_vec3d	vec_mult(t_vec3d vec1, t_vec3d vec2)
{
	t_vec3d	res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = vec1.z * vec2.x - vec1.x * vec2.z;
	res.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (res);
}

t_vec3d	vec_norm(t_vec3d ray)
{
	t_vec3d	normal;

	normal.x = ray.x / vec_lenth(ray);
	normal.y = ray.y / vec_lenth(ray);
	normal.z = ray.z / vec_lenth(ray);
	return (normal);
}

t_vec3d	turn_normal(t_vec3d normal, t_vec3d ray_dir)
{
	double	res;

	res = vec_dot(ray_dir, normal);
	if (res < 0)
		return (vec_norm(normal));
	return (vec_sc_mult(vec_norm(normal), -1.));
}
