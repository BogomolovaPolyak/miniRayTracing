/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:51:42 by natali            #+#    #+#             */
/*   Updated: 2021/04/26 15:03:15 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_win(t_scene *scene, int save)
{
	scene->init = mlx_init();
	if (!scene->init)
		ft_exit(scene, "Cannot init mlx", EXIT_FAILURE);
	if (!save)
	{
		scene->win = mlx_new_window(scene->init,
				scene->width, scene->height, "MINIRT");
		if (!scene->win)
			ft_exit(scene, "Cannot open mlx window", EXIT_FAILURE);
	}
	scene->img.img = mlx_new_image(scene->init, scene->width, scene->height);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
}
