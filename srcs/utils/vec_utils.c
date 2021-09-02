/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:30:04 by natali            #+#    #+#             */
/*   Updated: 2021/04/20 22:20:27 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d	vec_sum(t_vec3d vec1, t_vec3d vec2)
{
	t_vec3d	sum;

	sum.x = vec1.x + vec2.x;
	sum.y = vec1.y + vec2.y;
	sum.z = vec1.z + vec2.z;
	return (sum);
}

t_vec3d	vec_diff(t_vec3d vec1, t_vec3d vec2)
{
	t_vec3d	diff;

	diff.x = vec1.x - vec2.x;
	diff.y = vec1.y - vec2.y;
	diff.z = vec1.z - vec2.z;
	return (diff);
}

double	vec_lenth(t_vec3d vec)
{
	double	lenth;

	lenth = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (lenth);
}

double	vec_dist(t_vec3d vec1, t_vec3d vec2)
{
	t_vec3d	diff;
	double	dist;

	diff = vec_diff(vec1, vec2);
	dist = vec_lenth(diff);
	return (dist);
}
