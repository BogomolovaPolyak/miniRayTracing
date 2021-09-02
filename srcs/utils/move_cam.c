/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:52:59 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/25 06:41:27 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_cam(t_camera *cam, int width, int height)
{
	while (cam)
	{
		cam->canvas.width = tan(cam->FOV / 2. * (M_PI / 180)) * 2;
		cam->canvas.x_pixel = cam->canvas.width / width;
		cam->canvas.y_pixel = cam->canvas.width
			/ (width / (double)height) / height;
		cam = cam->next;
	}
}

t_vec3d	matrix_mult(t_vec3d vec, t_matrix mtrx)
{
	t_vec3d	res;

	res.x = vec.x * mtrx.m[0][0] + vec.y * mtrx.m[1][0]
		+ vec.z * mtrx.m[2][0] + mtrx.m[3][0];
	res.y = vec.x * mtrx.m[0][1] + vec.y * mtrx.m[1][1]
		+ vec.z * mtrx.m[2][1] + mtrx.m[3][1];
	res.z = vec.x * mtrx.m[0][2] + vec.y * mtrx.m[1][2]
		+ vec.z * mtrx.m[2][2] + mtrx.m[3][2];
	return (res);
}

t_vec3d	check_random_vec(t_vec3d dir)
{
	t_vec3d	tmp;

	if (dir.x == 0 && dir.y == 1 && dir.z == 0)
		tmp = (t_vec3d){0, 0, -1};
	else if (dir.x == 0 && dir.y == -1 && dir.z == 0)
		tmp = (t_vec3d){0, 0, 1};
	else
		tmp = (t_vec3d){0, 1, 0};
	return (tmp);
}

t_matrix	look_at(t_vec3d view_point, t_vec3d dir)
{
	t_matrix	m;
	t_vec3d		tmp;
	t_vec3d		right;
	t_vec3d		up;

	tmp = check_random_vec(dir);
	right = vec_norm(vec_mult(tmp, dir));
	up = vec_norm(vec_mult(dir, right));
	m.m[0][0] = right.x;
	m.m[0][1] = right.y;
	m.m[0][2] = right.z;
	m.m[0][3] = 0;
	m.m[1][0] = up.x;
	m.m[1][1] = up.y;
	m.m[1][2] = up.z;
	m.m[1][3] = 0;
	m.m[2][0] = dir.x;
	m.m[2][1] = dir.y;
	m.m[2][2] = dir.z;
	m.m[3][3] = 0;
	m.m[3][0] = view_point.x;
	m.m[3][1] = view_point.y;
	m.m[3][2] = view_point.z;
	m.m[3][3] = 1;
	return (m);
}
