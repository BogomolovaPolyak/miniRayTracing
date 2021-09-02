/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:05:48 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/25 07:05:00 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	calc_bright(t_vec3d obj_normal, t_vec3d light_dir, double light_br)
{
	double	dot;
	double	br;

	dot = vec_dot(obj_normal, light_dir);
	if (dot > 0.00001)
	{
		br = light_br * dot
			/ (vec_lenth(obj_normal) * vec_lenth(light_dir));
		return (br);
	}
	return (0);
}

t_color	calc_light(t_ambient amb, t_closest cl, t_light *light, t_obj *obj)
{
	t_vec3d		l_dir;
	t_color		res;
	double		br;
	t_closest	puk;

	res = color_mix(cl.color, amb.intense);
	while (light)
	{
		br = 0;
		l_dir = vec_diff(light->point, cl.inter);
		puk = find_closest(obj, cl.inter, l_dir, (t_range){0.00001, 1});
		if (puk.t == INFINITY)
		{
			br = calc_bright(cl.normal, l_dir, light->br);
			if (br)
				res = color_sum(res,
						color_mix(cl.color, light_bright(light->color, br)));
		}
		light = light->next;
	}
	check_color(&res);
	return (res);
}
