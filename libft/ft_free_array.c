/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:31:27 by natali            #+#    #+#             */
/*   Updated: 2021/04/25 06:15:54 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	*ft_free_array(char **array)
{
	int	size;
	int	i;

	size = arr_len(array);
	i = 0;
	if (array && *array)
	{
		while (i <= size)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		*array = NULL;
	}
	return (NULL);
}
