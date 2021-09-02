/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 23:10:56 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/13 18:40:40 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	int		i;
	int		len;

	while (ft_check(*s1, set) == 1)
		s1++;
	if (!*s1)
	{
		copy = malloc(1);
		copy[0] = '\0';
		return (copy);
	}
	i = 0;
	len = ft_strlen(s1) - 1;
	while (ft_check(s1[len--], set) == 1)
		i++;
	len = ft_strlen(s1) - i + 1;
	copy = malloc(len);
	if (!copy)
		return (NULL);
	i = 0;
	while (len-- > 1)
		copy[i++] = *s1++;
	copy[i] = '\0';
	return (copy);
}
