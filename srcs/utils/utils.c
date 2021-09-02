/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:40:47 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/26 19:19:38 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		ft_exit(NULL, "Cannot allocate memory", EXIT_FAILURE);
	scene->width = 0;
	scene->height = 0;
	scene->ambient.ratio = -1;
	scene->camera = NULL;
	scene->light = NULL;
	scene->obj = NULL;
	scene->init = NULL;
	scene->win = NULL;
	return (scene);
}

void	free_scene(t_scene *scene)
{
	while (scene->camera)
	{
		free(scene->camera);
		scene->camera = scene->camera->next;
	}
	while (scene->light)
	{
		free(scene->light);
		scene->light = scene->light->next;
	}
	while (scene->obj)
	{
		if (scene->obj->data)
			free(scene->obj->data);
		free(scene->obj);
		scene->obj = scene->obj->next;
	}
	if (scene)
		free(scene);
}

void	ft_exit(t_scene *scene, char *message, int status)
{
	if (scene && scene->init && scene->img.img)
		mlx_destroy_image(scene->init, scene->img.img);
	if (scene && scene->init && scene->win)
		mlx_destroy_window(scene->init, scene->win);
	free_scene(scene);
	if (status)
		printf("Error\n%s\n", message);
	else
		printf("%s\n", message);
	exit(status);
}
