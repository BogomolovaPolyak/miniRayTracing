/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:59:32 by natali            #+#    #+#             */
/*   Updated: 2021/04/27 14:55:11 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_normal(t_vec3d *normal)
{
	static int	once;

	if (normal->x < -1.0 || normal->x > 1.0
		|| normal->y < -1.0 || normal->y > 1.0
		|| normal->z < -1.0 || normal->z > 1.0)
		return (1);
	if (normal->x == 0 && normal->y == 0 && normal->z == 0)
	{
		normal->z = 1;
		if (once != 1)
		{
			printf("Sorry not sorry I've changed your trapping normal\n");
			once = 1;
		}
	}
	return (0);
}

int	rt_atoi(char *str, char **spl, t_scene *scene)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	if ((*str != '-' && !(ft_isdigit(*str))) || !str)
	{
		ft_free_array(spl);
		ft_exit(scene, "Your scene is incorrect, do your best", EXIT_FAILURE);
	}
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

double	rt_atof(char *str, char **spl, t_scene *scene)
{
	double	res;
	int		sign;

	sign = 0;
	res = rt_atoi(str, spl, scene);
	if (*str == '-')
		sign += 1;
	while ((*str == '-' || ft_isdigit(*str)) && *str)
		str++;
	if (*str == '.')
		str++;
	if (!*str)
		return (res);
	if (res < 0 || (res == 0 && sign))
		res -= rt_atoi(str, spl, scene) / pow(10, ft_strlen(str));
	else
		res += rt_atoi(str, spl, scene) / pow(10, ft_strlen(str));
	while (ft_isdigit(*str) && *str)
		str++;
	if (*str)
	{
		ft_free_array(spl);
		ft_exit(scene, "Your scene is incorrect, do your best", EXIT_FAILURE);
	}
	return (res);
}
