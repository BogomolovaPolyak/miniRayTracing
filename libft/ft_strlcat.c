/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:15:24 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/13 18:33:54 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if ((size_t)ft_strlen(dst) >= dstsize)
		return (dstsize + src_len);
	else
		dst_len = ft_strlen(dst);
	if (!*src)
		return (dst_len);
	while (*dst)
		dst++;
	while ((dstsize - 1 > dst_len) && *src)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
