/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 22:04:04 by natali            #+#    #+#             */
/*   Updated: 2021/04/25 01:58:04 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_color	color_mix(t_color c1, t_color c2)
{
	t_color	mix;

	mix.R = c1.R * c2.R / 255;
	mix.G = c1.G * c2.G / 255;
	mix.B = c1.B * c2.B / 255;
	return (mix);
}

t_color	color_sum(t_color c1, t_color c2)
{
	t_color	sum;

	sum.R = c1.R + c2.R;
	sum.G = c1.G + c2.G;
	sum.B = c1.B + c2.B;
	return (sum);
}

t_color	light_bright(t_color color, double bright)
{
	t_color	res;

	res.R = (double)color.R * bright;
	res.G = (double)color.G * bright;
	res.B = (double)color.B * bright;
	return (res);
}

void	check_color(t_color *res)
{
	if (res->R > 255)
		res->R = 255;
	if (res->G > 255)
		res->G = 255;
	if (res->B > 255)
		res->B = 255;
}
