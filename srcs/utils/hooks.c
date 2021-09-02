/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:56:42 by natali            #+#    #+#             */
/*   Updated: 2021/04/26 22:35:14 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	red_cross(t_scene *scene)
{
	ft_exit(scene, "Bye, I hope you enjoyed it", EXIT_SUCCESS);
	return (0);
}

int	press_key(int key_code, t_scene *sc)
{
	if (key_code == KEY_ESC)
		ft_exit(sc, "Bye, there are no leaks here, I bet", EXIT_SUCCESS);
	else if (key_code == KEY_RIGHT)
	{
		if (sc->camera->next)
		{
			sc->camera = sc->camera->next;
			create_canvas(sc, 0);
		}
	}
	else if (key_code == KEY_LEFT)
	{
		if (sc->camera->prev)
		{
			sc->camera = sc->camera->prev;
			create_canvas(sc, 0);
		}
	}
	return (0);
}
