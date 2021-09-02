/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:27:23 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 00:31:42 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*last_obj(t_obj *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	put_back_obj(t_obj **start, t_obj *new)
{
	t_obj	*last;

	if (!*start)
	{
		*start = new;
		return ;
	}
	last = last_obj(*start);
	last->next = new;
}

void	parse_obj(char **splitted, t_scene *scene)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->data = NULL;
	obj->next = NULL;
	put_back_obj(&scene->obj, obj);
	if (!(ft_strcmp(splitted[0], "sp")) && arr_len(splitted) == 4)
		parse_sphere(obj, scene, splitted);
	else if (!(ft_strcmp(splitted[0], "pl")) && arr_len(splitted) == 4)
		parse_plane(obj, scene, splitted);
	else if (!(ft_strcmp(splitted[0], "sq")) && arr_len(splitted) == 5)
		parse_square(obj, scene, splitted);
	else if (!(ft_strcmp(splitted[0], "cy")) && arr_len(splitted) == 6)
		parse_cylinder(obj, scene, splitted);
	else if (!(ft_strcmp(splitted[0], "tr")) && arr_len(splitted) == 5)
		parse_triangle(obj, scene, splitted);
	else
	{
		ft_free_array(splitted);
		ft_exit(scene, "Your scene is incorrect, do your best", EXIT_FAILURE);
	}
}
