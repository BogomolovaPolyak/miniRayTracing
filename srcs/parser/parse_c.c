/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:13:20 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 14:54:31 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*last_camera(t_camera *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	put_back_camera(t_camera **start, t_camera *new)
{
	t_camera	*last;

	if (!*start)
	{
		new->prev = NULL;
		*start = new;
		return ;
	}
	last = last_camera(*start);
	last->next = new;
	new->prev = last;
}

void	parse_c(char **spl, t_scene *scene)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
	{
		ft_free_array(spl);
		ft_exit(scene, "Cannot allocate memory", EXIT_FAILURE);
	}
	put_back_camera(&scene->camera, camera);
	camera->view_point = split_vectors(spl[1], scene, spl);
	camera->normal = split_vectors(spl[2], scene, spl);
	camera->FOV = rt_atof(spl[3], spl, scene);
	if (check_normal(&(camera->normal)) || camera->FOV < 0 || camera->FOV > 180)
	{
		ft_free_array(spl);
		ft_exit(scene, "Sorry, camera is broken", EXIT_FAILURE);
	}
	if (camera->FOV == 180)
		camera->FOV = 179;
	camera->normal = vec_norm(camera->normal);
	camera->canvas = (t_canvas){0, 0, 0};
	camera->next = NULL;
}
