/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:11:05 by natali            #+#    #+#             */
/*   Updated: 2021/04/26 21:08:08 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_str(char *str)
{
	int	dot;

	dot = 0;
	if (!str)
		return (1);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' && dot)
			return (1);
		if (!(ft_isdigit(*str)) && *str != '.')
			return (1);
		if (*str == '.')
			dot++;
		str++;
	}
	return (0);
}

int	arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i == 0)
		i = 1;
	return (i);
}

t_color	split_colors(char *str, char **array, t_scene *scene)
{
	t_color	color;
	char	**values;

	values = ft_split(str, ',');
	if (!values || arr_len(values) != 3 || check_str(values[0])
		|| check_str(values[1]) || check_str(values[2]))
	{
		ft_free_array(values);
		ft_free_array(array);
		ft_exit(scene, "Color values are incorrect", EXIT_FAILURE);
	}
	color.R = (int)rt_atof(values[0], array, scene);
	color.G = (int)rt_atof(values[1], array, scene);
	color.B = (int)rt_atof(values[2], array, scene);
	ft_free_array(values);
	if (color.R < 0 || color.G < 0 || color.B < 0
		|| color.R > 255 || color.G > 255 || color.B > 255)
	{
		ft_free_array(array);
		ft_exit(scene, "Color values are incorrect", EXIT_FAILURE);
	}
	return (color);
}

t_vec3d	split_vectors(char *str, t_scene *scene, char **array)
{
	t_vec3d	vector;
	char	**values;

	values = ft_split(str, ',');
	if (!values || arr_len(values) != 3 || check_str(values[0])
		|| check_str(values[1]) || check_str(values[2]))
	{
		ft_free_array(values);
		ft_free_array(array);
		ft_exit(scene, "Something wrong with vectors", EXIT_FAILURE);
	}
	vector.x = rt_atof(values[0], array, scene);
	vector.y = rt_atof(values[1], array, scene);
	vector.z = rt_atof(values[2], array, scene);
	ft_free_array(values);
	return (vector);
}

char	**rt_split_set(char *str, char *set, t_scene *scene)
{
	char	**spl;

	spl = ft_split_set(str, set);
	free(str);
	if (!spl)
		ft_exit(scene, "Cannot allocate memory", EXIT_FAILURE);
	return (spl);
}
