/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:05:38 by natali            #+#    #+#             */
/*   Updated: 2021/04/25 01:51:02 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*last_light(t_light *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	put_back_light(t_light **start, t_light *new)
{
	t_light	*last;

	if (!*start)
	{
		*start = new;
		return ;
	}
	last = last_light(*start);
	last->next = new;
}

void	parse_l(char **spl, t_scene *scene)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
	{
		ft_free_array(spl);
		ft_exit(scene, "Cannot allocate memory", EXIT_FAILURE);
	}
	put_back_light(&scene->light, light);
	light->br = rt_atof(spl[2], spl, scene);
	if (light->br < 0 || light->br > 1.0)
	{
		ft_free_array(spl);
		ft_exit(scene,
			"Shine bright like a diamond but in range [0.0,1.0]", EXIT_FAILURE);
	}
	light->point = split_vectors(spl[1], scene, spl);
	light->color = split_colors(spl[3], spl, scene);
	light->next = NULL;
}
