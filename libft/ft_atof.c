/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 21:18:02 by natali            #+#    #+#             */
/*   Updated: 2021/04/13 18:53:54 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	res;

	res = 0;
	res = ft_atoi(str);
	while ((*str == '-' || ft_isdigit(*str)) && *str)
		str++;
	if (*str == '.')
		str++;
	if (res < 0)
		res -= ft_atoi(str) / pow(10, ft_strlen(str));
	else
		res += ft_atoi(str) / pow(10, ft_strlen(str));
	return (res);
}
